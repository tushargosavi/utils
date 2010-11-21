/*
 * Copyright (c) 1998-1999 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#pragma ident	"@(#)example1.c	1.1	99/11/19 SMI"

#include <sys/mdb_modapi.h>
#include <sys/sysinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stab_parser.h>

extern int read_object(char *name);
extern struct stab_entry *stabs_list_head;
extern int view_operations(uintptr_t addr, uint_t flags, unsigned int argc, const mdb_arg_t *argv);

static int
read_defs(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	char *filename;

	if (argv->a_type == MDB_TYPE_STRING)
		filename = (char*)argv->a_un.a_str;

	read_object(filename);

    return (DCMD_OK);
	
}

void dump_data(unsigned char *data, int len)
{
	int i;

	printf("\n");
	for(i =1; i< len; i++) 
	{
		printf("0x%02x ", data[i-1]);
		if (i%10 == 0) printf("\n");
	}
	printf("\n");
}


static int
print_struct_cmd(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
        char *name;
        struct struct_def *def;
        char *data;
        int ret;

        name = (char*)argv->a_un.a_str;
        def = search_struct(name);
        if (def == NULL) return DCMD_ERR;

        data = (char *)mdb_zalloc((ssize_t)def->size, UM_SLEEP);
        ret = mdb_vread(data, def->size, addr);
        if (ret < 0) return DCMD_ERR;

		print_struct(def, addr, data);
		return DCMD_OK;
}

static int
print_offset_cmd(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
        char *name;
        struct struct_def *def;
        char *data;
        int ret;

        name = (char*)argv->a_un.a_str;
        def = search_struct(name);
        if (def == NULL) return DCMD_ERR;

        data = (char *)mdb_zalloc((ssize_t)def->size, UM_SLEEP);

		print_struct(def, 0, data);
		return DCMD_OK;
}


static int
print_link_list(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	char *name, *member_name;
	struct struct_def *def;
	char *data ;
	uintptr_t ptr;
	int ret;
	int offset =0;
	int count, max;
	max = 1000;

	if (argc < 2) {
		mdb_warn("Usage print_llist <struct name> <next member> [max count]\n");
		return DCMD_ERR;
	}
	name = (char*)argv->a_un.a_str;
	argv++;
	member_name = (char*)argv->a_un.a_str;


	def = search_struct(name);
	if (def == NULL) return DCMD_ERR;

	data = (char *)mdb_zalloc((ssize_t)def->size, UM_SLEEP);
	offset = get_offset(def, member_name);
	if (offset < 0) return DCMD_ERR;
	offset /= 8;

	ptr = addr;
	count = 0;
	while (ptr != NULL && count < max) {
		ret = mdb_vread(data, def->size, ptr);
		if (ret < 0) return DCMD_ERR;
		print_struct(def, ptr, data);
		ptr = *(uintptr_t*)(data + offset);
		count ++;
		printf("\n\n");
	}
	return DCMD_OK;
}


static int
print_array_cmd(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	char *name, *member_name;
	struct struct_def *def;
	char *data ;
	uintptr_t ptr;
	int ret;
	int offset =0;
	int count, max;
	int i;

	max = 1000;
	
	if (argc < 2) {
		mdb_warn("Usage print_array <struct name> count\n");
	}
	name = (char*)argv->a_un.a_str;
	argv++;
	count = argv->a_un.a_val;
	printf("count is =%d\n", count);

	def = search_struct(name);
	if (def == NULL) return DCMD_ERR;

	data = (char *)mdb_zalloc((ssize_t)def->size, UM_SLEEP);

	ptr = addr;
	i = 0;
	while (i < count) {
		ret = mdb_vread(data, def->size, ptr);
		if (ret < 0) return DCMD_ERR;
		print_struct(def, ptr, data);
		ptr = (uintptr_t)(ptr + def->size);
		i ++;
		printf("\n\n");
	}
	mdb_free(data, (ssize_t)def->size);
	return DCMD_OK;
}


static int
print_parray_cmd(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	char *name, *member_name;
	struct struct_def *def;
	char *data; 
	uintptr_t *addr_buf;
	int ret;
	int offset =0;
	int count, max;
	int i;

	max = 1000;
	if (argc < 2) {
		mdb_warn("Usage print_array <struct name> count\n");
	}
	name = (char*)argv->a_un.a_str;
	argv++;
	count = atoi(argv->a_un.a_str);

	printf("count is =%d\n", count);

	def = search_struct(name);
	if (def == NULL) return DCMD_ERR;

	data = (char *)mdb_zalloc((ssize_t)def->size, UM_SLEEP);
	addr_buf = (uintptr_t*)mdb_zalloc((sizeof(uintptr_t) * count), UM_SLEEP);
	
	ret = mdb_vread(addr_buf, (sizeof(uintptr_t) * count), addr);
	i =0;
	while (i < count) {
		printf("\nreading from address :0x%llx\n", addr_buf[i]);
		ret = mdb_vread(data, def->size, addr_buf[i]);
		if (ret < 0) return DCMD_ERR;
		print_struct(def, addr_buf[i], data);
		i ++;
		printf("\n\n");
	}
	mdb_free(addr_buf, (sizeof(uintptr_t) * count));
	mdb_free(data, (ssize_t)def->size);
	return DCMD_OK;
}


static int
print_hash_cmd(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	char *name, *member_name;
	struct struct_def *def;
	char *data; 
	uintptr_t *addr_buf;
	int ret;
	int offset =0;
	int count, max;
	uintptr_t ptr;
	int i;

	max = 1000;
	if (argc < 2) {
		mdb_warn("Usage print_array <struct name> count\n");	
		return DCMD_ERR;
	}
	count = atoi(argv->a_un.a_str);
	argv++;
	name = (char*)argv->a_un.a_str;
	argv++;
	member_name = (char*)argv->a_un.a_str;

	printf("count is =%d\n", count);

	def = search_struct(name);
	if (def == NULL) return DCMD_ERR;

    offset = get_offset(def, member_name);
	if (offset < 0) return DCMD_ERR;
    offset /= 8;

	data = (char *)mdb_zalloc((ssize_t)def->size, UM_SLEEP);
	addr_buf = (uintptr_t*)mdb_zalloc((sizeof(uintptr_t) * count), UM_SLEEP);
	
	ret = mdb_vread(addr_buf, (sizeof(uintptr_t) * count), addr);
	i =0;
	while (i < count) {
	    ptr = addr_buf[i];
  		while (ptr != NULL ) {
			ret = mdb_vread(data, def->size, ptr);
			if (ret < 0) return DCMD_ERR;
			print_struct(def, ptr, data);
			ptr = *(uintptr_t*)(data + offset);
	        printf("\n\n");
    	}
		i++;
	}
	mdb_free(addr_buf, (sizeof(uintptr_t) * count));
	mdb_free(data, (ssize_t)def->size);
	return DCMD_OK;
}


/*
 * MDB module linkage information:
 *
 * We declare a list of structures describing our dcmds, and a function
 * named _mdb_init to return a pointer to our module information.
 */

static const mdb_dcmd_t dcmds[] = {
	{ "rddefs", " filename", "Reads data defs from file", read_defs },
	{ "print_struct", "name", "Print formated struct", print_struct_cmd},
	{ "print_offset", "name", "Print member offset info", print_offset_cmd},
	{ "print_list", "name", "Print link list", print_link_list},
	{ "print_array", "name", "Print array", print_array_cmd},
	{ "print_parray", "name", "Print array of pointer", print_parray_cmd},
	{ "print_hash", "name", "Print hash table", print_hash_cmd},
	{ "view", "name", "Manage data views" , view_operations }, 
	{ NULL }
};

static const mdb_modinfo_t modinfo = {
	MDB_API_VERSION, dcmds, NULL
};

const mdb_modinfo_t *
_mdb_init(void)
{
	return (&modinfo);
}

