#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stab_parser.h>

extern type_hash_t type_table[];

int get_offset(struct struct_def *sdef, char *member_name)
{
    struct struct_member *member;
    struct type_info *tinfo;
    int end;

    if (!sdef) {
        printf("Structure not found\n");
        return -1;
    }
    member = sdef->members;
    while(member != NULL) {
        if (strcmp(member->name, member_name)== 0) 
			return member->offset;
	
        member = member->next;
    }
	return -1;
}

int basic_type(struct type_info *tinfo)
{
    switch(tinfo->info.btype.size) {
        case 0 : return VOID;
        case 1 : return ((tinfo->info.btype.sign)? CHAR : UCHAR);
        case 2 : return ((tinfo->info.btype.sign)? SHORT: USHORT);
        case 4 : return ((tinfo->info.btype.sign)? INT: UINT);
        case 8 : return ((tinfo->info.btype.sign)? LONG: ULONG);
    }
    return ERROR;
}

int base_type_info(struct type_info *tinfo)
{
    switch (tinfo->type) {
        case BASIC_TYPE :
            return basic_type(tinfo);
        case FLOAT_TYPE :
            return FLOAT_TYPE;
        case EQUAL :
            return base_type(tinfo->id);
        case POINTER :
            return TYPE_POINTER;
        case ARRAY :
            return ARRAY;
        case FORWARD_REF :
			return TYPE_STRUCT;
		case FUNCTION_PTR :
			return TYPE_FUNCTION_PTR;
        default :
            return ERROR;
    }
}

int base_type(int id)
{
    struct type_table_entry *ptr;
    int index=ID_HASH(id);
    ptr = type_table[index].head;

    while (ptr) {
        if (ptr->id == id) break;
        ptr=ptr->next;
    }
    if (!ptr) {
        printf("id (%d,%d) not found\n", (id >> 16) , (id & 0xFF));
        return ERROR;
    }

    switch (ptr->type) {
    case TYPEDEF :
        return base_type_info(ptr->info.tdef->type);
    case STRUCTURE :
        return TYPE_STRUCT;
    case UNION :
        return TYPE_BASIC_UNION;
    case TYPE_INFO :
        return base_type_info(ptr->info.ptr);
    case ENUM :
        return TYPE_ENUM;
    }
    return ERROR;
}


