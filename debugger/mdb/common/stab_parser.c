#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>

#include <stab_parser.h>

#define STR_SIZE (4000)
static char str[STR_SIZE];
struct stab_entry *stabs_list_tail;
struct stab_entry *stabs_list_head;


void read_file(FILE *fin)
{
	char ch;
	int i;

	memset(str,0,STR_SIZE);

	while (fgets(str, STR_SIZE-1, fin)) {
		parse_entry(str);
	}

	/*
	while (!eof(fin)) {
		while (read(fin, &ch, 1) != '\n') {
			if (eof(fin)) break;
			str[i++] = ch;
		}
		str[i] =0;
		parse_entry(str);
	}
	*/
}

char *scan_till(char *str, char ch)
{
	while(*str!= '\0' && *str != ch) str++;
	return str;
}

int isletter(char c)
{
	if (c >= 'a' && c <= 'z') return 1;
	if (c >= 'A' && c <= 'A') return 1;
	if (c == '_') return 1;
	return 0;
}

char *scan_int(char *str, int *a)
{
	int num=0;
	while(*str >= '0' && *str <= '9') { num = num * 10 + (*str - '0'); str++; }
	*a = num;
	return str;
}

char *scan_str(char *str, char *dest) {
	int i=0;
	while (isletter(*str) && *str != '\0') dest[i++]=*str++;
	dest[i]=0;
	return str;
}

void parse_entry(char *str)
{
	int i=0;
	char *temp=str;
	struct stab_entry *entry;
		
	while (*temp ==' ' || *temp =='\t') temp++; 
	if (strncmp(temp,".stabs", 6)!=0) return;
	while (*temp != '"') temp++; temp++;

	/* this is a .stab entry */
	entry = (struct stab_entry*)malloc(sizeof(struct stab_entry));
	memset(entry, 0 , sizeof(struct stab_entry));

	while(*temp !='"') entry->str[i++]=*temp++;
	temp ++; temp++; /* skip on , */
	sscanf(temp, "%d", &(entry->type));
	while (*temp++!= ','); 
	sscanf(temp, "%d", &(entry->other));
	while (*temp++!= ','); 
	sscanf(temp, "%d", &(entry->desc));
	while (*temp++!= ','); 
	sscanf(temp, "%d", &(entry->value));

	if (entry->type != 128) return;
	if (stabs_list_head == NULL) {
		stabs_list_head = stabs_list_tail = entry;
	} else {
		stabs_list_tail->next = entry;
		stabs_list_tail = entry;	
	}
}

void add_stab_entry(struct stab_entry *entry)
{
	int len =0;

	if (entry->type != 128) return;

	if (stabs_list_tail != NULL) {
		len = strlen((char*)stabs_list_tail->str);
		if (stabs_list_tail->str[len-1] == '\\') {
			if (stabs_list_tail->desc == entry->desc &&
				stabs_list_tail->type == entry->type &&
				stabs_list_tail->value == entry->value) 
			{
				printf("continuation entry found\n");
				/* This is continuation of previous entry */
				stabs_list_tail->str[len] = '\\';
			}
		}
	}

	if (stabs_list_head == NULL) {
		stabs_list_head = stabs_list_tail = entry;
	} else {
		stabs_list_tail->next = entry;
		stabs_list_tail = entry;
	}
}

void free_stab_entry_list()
{
	struct stab_entry *temp = stabs_list_head;
	struct stab_entry *to_free;

	while (temp != NULL) {
		to_free = temp;
		temp = to_free->next;
		free(temp);	
	}		
}

/* format of stab entry is 
 * name:TYPE(NUM,NUM)=<other type>....
 * 
 * name:T(NUM,NUM)=s<size><structure members>
 * name:t(NUM,NUM)=(NUM,NUM)
 * name:t(NUM,NUM)=xs<name>
 */

void parse_stab_entry(struct stab_entry *entry)
{
	char name[80];
	int i=0;
	char *str=(char*)entry->str;
		
	while (*str != ':' ) name[i++]=*str++;	name[i] =0;
	str++;
	if (!((*str == 'T') || (*str == 't'))) return;
	if (*str == 't') parse_type_defs(name, str);
	else parse_struct_defs(name, str);	
}


void parse_type_defs(char *name, char *str)
{
	int id1, id2;
	struct type_info *info;
	struct type_def *tdef;
	
	tdef = (struct type_def*)malloc(sizeof(struct type_def));
	bzero(tdef, sizeof(struct type_def));
	
	info=new_member_type();
	strcpy(tdef->name, name);
	str++;
	sscanf(str,"(%d,%d)", &id1, &id2);
	tdef->id = MAKEID(id1, id2);
	str=scan_till(str, ')'); str++;
	str = member_type(str, info);
	tdef->type = info->dep_type;
	free(info);
	add_type_def(tdef);
}

void parse_struct_defs(char *name, char *str)
{
	int id1, id2;
	struct struct_member *member;
	int size;
	struct struct_member *last_member= NULL;
	struct struct_def *def;
	
	def = (struct struct_def*)malloc(sizeof(struct struct_def));
	bzero(def, sizeof(struct struct_def));
	
	strcpy(def->name, name);
	str++;
	sscanf(str,"(%d,%d)", &id1, &id2);
	def->id = MAKEID(id1, id2);
	str = scan_till(str, ')'); str++;
	str++;
	
	
	switch(*str) {
	case 's' :
	case 'u' :
	
		if (*str == 's') def->type = TYPE_STRUCTURE;
		else def->type = TYPE_UNION;
		
		str++;
		str = scan_int(str, &size);
		def->size = size;
	
		if (*str == '@')  { str += 3; }
	
		while((member = parse_one_member(&str)) != NULL) {
			/* add scaned member to member list */
			if (!last_member) {
				def->members = last_member = member;
			} else {
				last_member->next = member;
				last_member = member;
			}
		}
		
		add_struct_def(def);
		break;
		
	case 'e' :
		def->type = TYPE_ENUM;
		def->size = 4;
		add_struct_def(def);
		break;
		
	default :
		printf("parse_struct_defs not handled str=%s\n", str);
		return;
	}
	return;
}

struct struct_member *parse_one_member(char **sstr)
{
	char name[80];
	int i;
	int id1, id2;

	struct type_info *mtype;
	struct struct_member *member;
	
	char *str = *sstr;
	
	while (*str == ';') str++;
	while (*str == '\\') str++;

	if (str[0] == '\0') {
		return NULL;
	}

	
	member = (struct struct_member*)malloc(sizeof(struct 
				struct_member));
	bzero(member, sizeof(struct struct_member));
	
	mtype = new_member_type();
	i=0;
	while (*str != ':') name[i++] = *str++;
	name[i]=0; str++;
	strcpy(member->name, name);
	
	sscanf(str,"(%d,%d)", &id1, &id2);
	str = scan_till(str, ')'); str++;
	mtype->id = MAKEID(id1, id2);
	str = member_type(str, mtype);
	
	member->type = mtype;
	str++; /* skip ',' */
	sscanf(str,"%d,%d;", &(member->offset), &(member->size));
	str=scan_till(str, ';'); str++;
	*sstr = str;
	return member;
}

char* member_type(char *str, struct type_info *mtype)
{
	struct type_info *info;
	int id1, id2;
	int size, offset, bit_size;
	
	if (*str == ',') return str;
	if (*str != '=') return str;
	/* This is entry for '=' we need to scan and decide for which this entry
	 * is defined and update the passed structured accordingly 
	 */
	
	info = new_member_type();
	mtype->dep_type = info;
	str++;
	switch(*str) {
	case '*' :
		str++;
		info->type = POINTER;
		if (*str =='(') {
			sscanf(str, "(%d,%d)", &id1, &id2);
			str = scan_till(str,')'); str++;
			info->id = MAKEID(id1, id2);
			str = member_type(str, info);
		} else if (*str == 'x') {
			str++;
        	if (*str++ != 's') return str;
	        str = scan_str(str, info->info.reftype.name); str++;
    	    add_to_forward_ref_table(info);
		}
		return str;
		
	case 'a' :
		info->type = ARRAY;
		str++;
		if (*str != 'r') return str;
		str++;
		sscanf(str, "(%d,%d)", &id1, &id2);
		str = scan_till(str, ')'); str++; str++;
		str = scan_int(str,&id1); str++; /* start index */
		str = scan_int(str, &id2); str++; /* end index */
		info->info.atype.start_index=id1;
		info->info.atype.end_index=id2;
		sscanf(str, "(%d,%d)", &id1, &id2);
		str = scan_till(str, ')'); str++;
		info->id = MAKEID(id1, id2);
		str = member_type(str, info);
		return str;
	
	case 'x' :
		str++;
		if (*str++ != 's') return str;
		info->type = FORWARD_REF;
		str = scan_str(str, info->info.reftype.name); str++;
		add_to_forward_ref_table(info);
		return str;
		
	case 'f' :
		str++;
		info->type = FUNCTION_PTR;
		sscanf(str, "(%d,%d)", &id1, &id2);
		str = scan_till(str, ')'); str++;
		info->id = MAKEID(id1, id2);
		str = member_type(str, info);
		return str;
	
	case 'B' :
		str++;
		info->type = VOLATILE;
		sscanf(str, "(%d,%d)", &id1, &id2);
		str = scan_till(str, ')'); str++;
		info->id = MAKEID(id1, id2);
		str = member_type(str, info);
		return str;
		
	case 'k' :
		str++;
		info->type = CONST;
		sscanf(str, "(%d,%d)", &id1, &id2);
		str = scan_till(str, ')'); str++;
		info->id = MAKEID(id1, id2);
		str = member_type(str, info);
		return str;
			
	case ',' :
		return str;

		
	/* This code only added to consider typedefs */
	case 'b' :
		info->type = BASIC_TYPE;
		str++;
		switch(*str) {
		case 's' : info->info.btype.sign = 1; break;
		case 'u' : info->info.btype.sign = 0; break;
		}
		str++;
		if (*str == 'c') {
			str++;
		}
		sscanf(str,"%d", &size);
		info->info.btype.size = size;
		str = scan_till(str, ';'); str++;
		sscanf(str,"%d",&offset);
		info->info.btype.offset= offset;
		str = scan_till(str, ';'); str++;
		sscanf(str, "%d", &bit_size);
		info->info.btype.bit_size = bit_size;
		str = member_type(str, info);
		return str;
	
	case 'R' :
		info->type = FLOAT_TYPE;
		str++;
		if (*str == '1') info->info.ftype.size = 4;
		else info->info.ftype.size = 8;
		str++; str++; str++;
		return str;
		
	case '(' :
		info->type = EQUAL;
		sscanf(str, "(%d,%d)", &id1, &id2);
		info->id = MAKEID(id1, id2);
		str = scan_till(str, ')'); str++;
		str = member_type(str, info);
		/* typdef */
		return str;
		
	default :
		printf("member_type not handled str =%s\n", str);
		break;
	}
	return str;
}

inline struct type_info *new_member_type()
{
	struct type_info *mtype;
	mtype = (struct type_info*)malloc(sizeof(struct type_info));
	if (!mtype) return NULL;
	bzero(mtype, sizeof(struct type_info));
	return mtype;
}
