#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <stab_parser.h>

/* hash table */
type_hash_t type_table[TYPE_TABLE_SIZE];


void add_into_type_table(struct type_table_entry *entry);

struct type_def *tdef_list_head;
struct type_def *tdef_list_tail;

struct struct_def *sdef_list_head;
struct struct_def *sdef_list_tail;

struct forward_ref_table_entry *fref_list_head;
struct forward_ref_table_entry *fref_list_tail;

void init_type_table()
{
	bzero(&type_table[0], sizeof(type_table));
}


void add_into_type_table(struct type_table_entry *entry)
{
	int index;
	
	index = ID_HASH(entry->id);
		
	if (type_table[index].head == NULL) {
		type_table[index].head = type_table[index].tail = entry;
	} else {
		type_table[index].tail->next = entry;
		type_table[index].tail = entry;
	}
}

struct type_table_entry *get_type_entry(int id)
{
	int index;
	struct type_table_entry *ptr = type_table[index].head;
	index = ID_HASH(id);

	while(ptr != NULL) {
		if (ptr->id == id) return ptr;
		ptr = ptr->next;
	}
	return NULL;
}

void add_to_forward_ref_table(struct type_info *tinfo) 
{
	struct forward_ref_table_entry *ptr;
	ptr = (struct forward_ref_table_entry *)malloc(sizeof(
			struct forward_ref_table_entry));
	bzero(ptr, sizeof(struct forward_ref_table_entry));
	ptr->ptr = tinfo;
	if (fref_list_head == NULL) {
		fref_list_head = fref_list_tail = ptr;
	} else {
		fref_list_tail->next = ptr;
		fref_list_tail = ptr;
	}
}


void add_struct_def(struct struct_def *def)
{
	struct type_table_entry *entry;
	struct type_info *tinfo;
	struct struct_member *member;
	
	entry = (struct type_table_entry*)malloc(sizeof(struct type_table_entry));
	bzero(entry, sizeof(struct type_table_entry));
	
	if (sdef_list_head == NULL) {
		sdef_list_head = sdef_list_tail = def;
	} else {
		sdef_list_tail->next = def;
		sdef_list_tail = def;
	}
	entry->id = def->id;
	entry->type = STRUCTURE;
	entry->info.sdef = def;
	add_into_type_table(entry);
	
	member = def->members;
	while(member != NULL) {
		tinfo = member->type;
		while (tinfo->dep_type) {
			entry = new_type_table_entry();
			entry->id = tinfo->id;
			entry->info.ptr = tinfo->dep_type;
			entry->type = TYPE_INFO;
			add_into_type_table(entry);
			tinfo = tinfo->dep_type;
		}
		member = member->next;
	}
}

void add_type_def(struct type_def *def)
{
	struct type_info *tinfo;
	struct type_table_entry *tentry;
		
	tentry = (struct type_table_entry*)malloc(sizeof(struct type_table_entry));
	bzero(tentry, sizeof(struct type_table_entry));
	
	if (tdef_list_head == NULL) {
		tdef_list_head = tdef_list_tail = def;
	} else {
		tdef_list_tail->next = def;
		tdef_list_tail = def;
	}
	
	tentry->id = def->id;
	tentry->info.tdef = def;
	tentry->type = TYPEDEF;
	add_into_type_table(tentry);
	
	tinfo = def->type;
	while (tinfo->dep_type) {
		tentry = new_type_table_entry();
		tentry->id = tinfo->id;
		tentry->info.ptr = tinfo->dep_type;
		tentry->type = TYPE_INFO;
		add_into_type_table(tentry);
		tinfo = tinfo->dep_type;
	}
}


struct struct_def* search_struct(char *name)
{
	struct struct_def *ptr=sdef_list_head;
	struct type_def *tptr = tdef_list_head;
	struct type_table_entry *hptr = NULL;
	int index;
	int id;

	while (ptr) {
		if (strcmp(ptr->name, name)==0) return ptr;
		else ptr = ptr->next;
	}

	while (tptr) {
		if (strcmp(tptr->name, name)==0) {
			id = tptr->type->id;
			index=ID_HASH(id);
			hptr = type_table[index].head;
			while (hptr) {
				if (hptr->id == id) break;
				hptr=hptr->next;
			}
			if (!hptr) {
				printf("id (%d,%d) not found", (id >> 16) , (id & 0xFF));
				return 0;
			}
			switch (hptr->type == STRUCTURE) return hptr->info.sdef;
		}
		tptr = tptr->next;
	}
	return NULL;
}


void process_forward_refs()
{
	struct forward_ref_table_entry *entry = fref_list_head;
	struct struct_def *sdef;
	
	while (entry) 
	{
		sdef= search_struct(entry->ptr->info.reftype.name);
		if (sdef == NULL) {
			/*
			 printf("forward ref %s not found in structure definitions\n", entry->ptr->info.reftype.name);
			*/
			entry = entry->next;
			continue;
		}
		entry->ptr->id = sdef->id;
		entry = entry->next;
	}
}

struct type_table_entry *new_type_table_entry()
{
	struct type_table_entry *ptr;
	ptr = (struct type_table_entry*)malloc(sizeof(struct type_table_entry));
	bzero(ptr, sizeof(struct type_table_entry));
	return ptr;
}
