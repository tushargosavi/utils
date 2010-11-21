#include <stdio.h>
#include <stdlib.h>
#include <gelf.h>
#include <stab.h>
#include <stdarg.h>
#include <stab_parser.h>
#include <sys/mdb_modapi.h>
#include <sys/sysinfo.h>

extern type_hash_t type_table[];

static int size_table[] = {
0x0, 0x1, 0x1, 0x2, 0x2, 0x4, 0x4, 0x8, 0x8, 0x8, 0x8, 0x8
};

static char str[MAX_STR_LEN]; /* array to store string read from core */
static char pstr[80];

long long start;
int indent;
int col;


int my_printf(char *fmt, ...)
{
	va_list va;
	int ret;

	memset(pstr, 0, 80);	
	va_start(va, fmt);
	ret = vsprintf(pstr, fmt, va);
	va_end(va);
	mdb_printf("%s", pstr);
	return ret;
}


static void indent_struct(long long offset)
{
	int i=0;

	if (sizeof (void*) == 8) 	
		col = my_printf("0x%012llx", start + (offset/8));
	else 
		col = my_printf("0x%08x", (long)start + ((long)offset/8));

	for (i=0; i < indent; i++) my_printf("  ");
	col += 2 * indent;
}

static void spaces()
{
	while (col++ != 40) my_printf(" ");
}

void print_struct(struct struct_def *sdef, long long base, char *data)
{
	start = base;
	indent =0;
	col = 0;
	print_struct_def(sdef, 0, data);
}

int print_struct_def(struct struct_def *sdef, long long offset, char *data)
{
	struct struct_member *member; 
	struct type_info *tinfo;
	int end;

	if (sdef->type == TYPE_ENUM) {
		my_printf("0x%lx",*((int*)data));		
		return 4;
	}
	if (sdef->type != TYPE_STRUCTURE) return 0;	
	if (!sdef) {
		my_printf("Structure not found\n");
		return 0;
	}
	
	my_printf("\n");
	indent_struct(offset);
	my_printf("struct %s size=%d {\n", sdef->name, sdef->size);
	indent++;
	member = sdef->members;
	while(member != NULL) {
		indent_struct(member->offset + offset);
		col += my_printf("%s",member->name); spaces();
		tinfo = member->type;
		print_id(tinfo->id, offset + member->offset, data + (member->offset / 8));
		end = member->offset + offset + member->size;
		member = member->next;
		my_printf("\n");
	}
	indent--;
	indent_struct(end); my_printf("}");
	return sdef->size;
}

int print_typedef(struct type_def *def, long long offset, char *data)
{
	struct type_info *tinfo = def->type;
	return print_type_info(tinfo, offset, data);
}

int print_array(struct type_info *tinfo, long long offset, char *data)
{
	int id ;
	int btype;
	int start, end;
	int i;
	char *ptr;
	int len=0;

	if (tinfo->type != ARRAY) return 0;
	id = tinfo->id;
	btype = base_type(id);

	if (btype == TYPE_STRUCT || btype == TYPE_BASIC_UNION 
		|| btype == TYPE_ENUM) 
		return 0;

	start = tinfo->info.atype.start_index;
	end = tinfo->info.atype.end_index;
	ptr = data;

	my_printf("[ ");
	for (i = start; i <= end ; i ++) {
		len = print_id(id, offset, ptr);
		if (i != end ) my_printf(" , ");
		ptr += len;
	}
	my_printf(" ]");

	if (btype == CHAR || btype == UCHAR) {
		my_printf(" \"%s\"", data);
	}
	return 0;
}


int print_type_info(struct type_info *tinfo, long long offset, char *data)
{
	int btype;
	int ret;
	GElf_Sym sym;

	switch(tinfo->type) {
		case BASIC_TYPE :
			if (tinfo->info.btype.sign) {
				switch (tinfo->info.btype.size) {
					case 1 : my_printf("0x%x", (char)*data); return 1;
					case 2 : my_printf("0x%hx", *((short*)data)); return 2;
					case 4 : my_printf("0x%lx",*((int*)data)); return 4;
					case 8 : my_printf("0x%llx", *((long*)data)); return 8;
				}
			} else {
					switch (tinfo->info.btype.size) {
					case 1 : my_printf("0x%x", (unsigned char)*data); return 1;
					case 2 : my_printf("0x%hx", *((unsigned short*)data)); return 2;
					case 4 : my_printf("0x%lx",*((unsigned int*)data)); return 4;
					case 8 : my_printf("0x%llx", *((unsigned long*)data)); return 8;
				}
			}
		break;
		
	case FLOAT_TYPE :
		switch(tinfo->info.ftype.size) {
		case 4 : my_printf(" float "); return 4;
		case 8 : my_printf(" double "); return 8;
		}
		break;
		
	case EQUAL :
		return print_id(tinfo->id, offset, data);
		
	case POINTER :
		/* print strings for char data type else print %p */
		if (sizeof(void*) == 8) 
			my_printf("0x%llx", *((long*)data)); 
		else 
			my_printf("0x%x", *((long*)data)); 

		btype = base_type(tinfo->id); 
		if (btype == CHAR || btype == UCHAR) {
			if (*(long*)data == 0) return 8;
			memset(str, 0, MAX_STR_LEN);
			ret = mdb_readstr(str, MAX_STR_LEN, *((long*)data));
			if (ret <= 0) return 8;
			my_printf(" \"%s\"", str);
		}
		if (btype == TYPE_FUNCTION_PTR) 
		{
			memset(str, 0, MAX_STR_LEN);
			ret= mdb_lookup_by_addr(*(long*)data, MDB_SYM_EXACT, str,
				MAX_STR_LEN, &sym);
			if (ret != -1) my_printf("  \"%s\" ", str);
		}
		return 8;

		
	case ARRAY :
		return print_array(tinfo, offset, data);
		
	case FORWARD_REF :
		return print_id(tinfo->id, offset, data);
		
	default :
		my_printf("error");
	}
}


int print_union(struct struct_def *def, long long offset, char *data)
{
	my_printf("Inside print_union %s\n", def->name);
	return def->size;
}

int print_id(int id, long long offset, char * data)
{
	struct type_table_entry *ptr;
	int index=ID_HASH(id);
	ptr = type_table[index].head;
	
	while (ptr) {
		if (ptr->id == id) break;
		ptr=ptr->next;
	}
	if (!ptr) {
		my_printf("id (%d,%d) not found", (id >> 16) , (id & 0xFF));
		return 0;
	}
	
	switch (ptr->type) {
	case TYPEDEF :
		return print_typedef(ptr->info.tdef, offset, data);
	case STRUCTURE :
		return print_struct_def(ptr->info.sdef, offset, data);
	case UNION :
		return print_union(ptr->info.sdef, offset, data);
	case TYPE_INFO :
		return print_type_info(ptr->info.ptr, offset, data);
	case ENUM :
		my_printf("0x%lx",*((unsigned int*)data));
		return 4;
	}
}
