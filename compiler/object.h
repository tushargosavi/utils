#ifndef OBJECT_H
#define OBJECT_H

enum ObjectType {
	T_INT,
	T_FLOAT,
	T_CHAR,
	T_STRING,
	T_BYTE_ARRAY,
	T_ARRAY,
	T_FUNCTION,
};

struct BArrayObject {
	char *data;
	int max_len;
	int len;
};

struct ArrayObject {
	struct Object_t **data;
	int max_len;
	int next_idx;
};

struct Object_t {
	unsigned int type;
	union {
		unsigned long intval;
		char *str;
		unsigned char *ptr;
		struct BArrayObject barr;
		struct ArrayObject arr;
	} value;
};

typedef struct Object_t Object;

#define get_type(o) (o->type)
#define get_int(o) (o->value.intval)
#define get_char(o) (o->value.intval)
#define get_string(o) ( o->value.str )
#define get_barray(o) ( o->value.ptr )
#define set_int_val(o, v) (o->value.intval = v)
#define set_string_val(o, str) (o->value.str = str)
#define set_char_val(o, c) (o->value.intval = c)

typedef Object*(*function_ptr)();

struct function_tbl_entry {
	char *name;
	function_ptr func;
	struct function_tbl_entry *next;
};

Object *create_int_obj(int val);
Object *create_str_obj(char *str);
Object *create_char_obj(char ch);
Object *convert_object(Object *o, int type);
Object *apply_operator(char *oper, Object *a, Object *b);
Object *minus(Object *a);
Object *array_access(Object *a, Object *b);
Object *promote(Object *a);
#endif

