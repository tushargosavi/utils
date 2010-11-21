#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/mdb_modapi.h>

#include <view.h>
#include <stab_parser.h>

struct view_entry *view_list_head  = NULL;
struct view_entry *view_list_tail  = NULL;
extern int start, indent, col;

struct view_command {
	char name[80];
	int (*func)(uintptr_t addr, unsigned int, unsigned int argc, const mdb_arg_t  *);
};

int view_create(uintptr_t addr, unsigned int, unsigned int argc, const mdb_arg_t  *);
int view_print(uintptr_t addr, unsigned int, unsigned int argc, const mdb_arg_t  *);
int view_delete(uintptr_t addr, unsigned int, unsigned int argc, const mdb_arg_t  *);
int view_append(uintptr_t addr, unsigned int, unsigned int argc, const mdb_arg_t  *);

struct view_command view_ops[] = {
	{ "create", view_create},
	{ "print", view_print },
	{ "delete", view_delete },
	{ "append", view_append },
	NULL
};

struct view_entry* search_view(char *name) 
{
	struct view_entry *temp = view_list_head;
	while (temp) {
		if (strcmp(temp->name, name) == 0) 
			return temp;
		temp = temp->next_view;
	}
	return NULL;	
}

void delete_entry(struct view_entry *entry)
{
	struct view_data *data = entry->data_head;
	struct view_data *temp = NULL;
	while (data != NULL) {
		temp = data;
		data = data->next;
		free(temp);
	}	
	free(entry);
}


void add_to_view(char *name, char *data, int len, long long addr)
{
	struct view_entry *entry = NULL;
	struct view_data *temp;

	entry = search_view(name);
	if (entry == NULL) return;

	temp = (struct view_data*) malloc(
		sizeof(struct view_data));
	temp->data = data;
	temp-> next = NULL;
	temp->addr = addr;

	if (entry->data_head == NULL) 
	{
		entry->data_head = entry->data_tail = temp;
	} else {
		entry->data_tail->next = temp;
		entry->data_tail = temp;
	}
}


void create_new_view(char *name, int id)
{
	struct view_entry *entry;

	entry = search_view(name);
	if (entry != NULL) 
		delete_entry(entry);
	
	entry = (struct view_entry*) malloc(
		sizeof(struct view_entry));
	bzero(entry, sizeof(struct view_entry));

	strcpy(entry->name, name);
	entry->id = id;
	entry->count = 0;

	if (view_list_head == NULL) {
		view_list_head = view_list_tail = entry;
	} else {
		view_list_tail->next_view = entry;
		view_list_tail = entry;
	}
}


int
view_operations(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	char *operations;
	int i=0;

	if (argc < 2) {
		mdb_warn("Usage view <command> <command parameters>\n");
		return DCMD_ERR;
	}

	operations = (char*)argv->a_un.a_str;
	argv++;
	i=0;
	while ( view_ops[i].name) {
		if (strcmp(view_ops[i].name, operations) == 0)
		{
			view_ops[i].func(addr, flags, argc-1 , argv);
			break;
		}
		i++;
	}
}

int 
view_delete(uintptr_t addr, unsigned int flags, unsigned int argc, const mdb_arg_t  *argv)
{
	return DCMD_OK;
}


int 
view_append(uintptr_t addr, unsigned int flags, unsigned int argc, const mdb_arg_t  *argv)
{
	return DCMD_OK;
}

int
view_create(uintptr_t addr, uint_t flags, unsigned int argc, const mdb_arg_t *argv)
{
	char *name, *member_name;
	char *struct_name, *next_member;
	char *type;
	int i;

	if (argc < 2) {
		mdb_warn("Usage new_view <view_name> [list|array|hash] <struct name> <next member> [max count]\n");
		return DCMD_ERR;
	}

	name = (char*)argv->a_un.a_str;
	argv++;
	type = (char*)argv->a_un.a_str;
	argv++;
	if (strcmp(type, "list") == 0) {
		mdb_printf("Creating view from list \n");
		struct_name = (char*)argv->a_un.a_str;
		argv++;
		next_member =  (char*)argv->a_un.a_str;
		return create_list_view(addr, name, struct_name, next_member);
	}
}

int create_list_view(uintptr_t addr, char *name, char *struct_name, char *member_name)
{
	struct struct_def *def;
	char *data;
	uintptr_t ptr;
	int offset;
	int count= 0;
	int max = 1000;
	int ret;
	
	printf("outside while look with addresss =0x%llx\n", addr);
	def = search_struct(struct_name);
	if (def == NULL) {
		mdb_printf("Struct %s not found\n", struct_name);
		return DCMD_ERR;
	}

	offset = get_offset(def, member_name);
	if (offset < 0) return DCMD_ERR;
	offset /= 8;

	ptr = addr;
	count = 0;

	printf("outside while look with addresss =0x%llx\n", ptr);
	create_new_view(name, def->id);	
	while (ptr != 0 && count < max) {
		printf("adding one entry at address=0x%llx\n", ptr);
		data = (char *)mdb_zalloc((ssize_t)def->size, UM_SLEEP);
		ret = mdb_vread(data, def->size, ptr);
		if (ret < 0) return DCMD_ERR;
		printf("adding one entry at address=0x%llx\n", ptr);
		add_to_view(name, data, def->size, ptr);
		ptr = *(uintptr_t*)(data + offset);
		
		count ++;
	}
	mdb_printf("Loaded %d entries\n", count);
	return DCMD_OK;
}



int 
view_print(uintptr_t addr, uint_t flags, unsigned int argc, const mdb_arg_t *argv)
{
	struct view_entry *entry;
	struct view_data *data;
	char *view_name;

	if (argc != 1 ) {
		mdb_warn("Usage print_view view_name\n");
		return DCMD_ERR;
	}

	view_name = (char*)argv->a_un.a_str;
	entry = search_view(view_name);
	if (entry == NULL) {
		mdb_warn("view %s not found\n", view_name);
		return DCMD_ERR;
	}
	
	data = entry->data_head;
	while (data != NULL) 
	{
		start = data->addr;
	    indent =0;
    	col = 0;

		print_id(entry->id, 0, data->data);	
		data = data->next;	
	}		
}


