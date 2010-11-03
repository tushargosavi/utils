#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
void log(const char *, ...);

struct function_tbl_entry *function_tbl = NULL;

/* 
 * A new function takes precedence over previos function
 * register with same name
 */
void register_function(char *name, Object*(*func1)())
{
	struct function_tbl_entry *entry = (struct function_tbl_entry*)malloc(
					sizeof(struct function_tbl_entry));
	entry->name = strdup(name);
	entry->func = func1;
	entry->next = function_tbl;
	function_tbl = entry;
}

/*
 * Return the c function with given name
 */
function_ptr getfunction(char *name)
{
	struct function_tbl_entry *tmp = function_tbl;
	while (tmp) {
		if (strcmp(name, tmp->name) == 0)
			return tmp->func;
		tmp = tmp->next;
	}
	return NULL;
}

Object *new_object(int type)
{
	Object *o = (Object*)malloc(sizeof(Object));
	o->type = type;
	return o;
}

Object* create_int_obj(int data)
{
	Object* o = new_object(T_INT);
	set_int_val(o, data);
	log("creating int object with value :%d %p\n", data, o);
	return o;
}

Object* create_str_obj(char *str)
{
	Object *o = new_object(T_STRING);
	set_string_val(o, str);
	return o;
}

Object* create_char_obj(char c)
{
	Object *o = new_object(T_CHAR);
	set_char_val(o, c);
	return o;
}

Object* create_barray_obj(char *c, int size)
{
	Object *o = new_object(T_BYTE_ARRAY);
	char *data = (char*)malloc(size);
	memcpy(data, c, size);
	o->value.barr.data = data;
	o->value.barr.len = size;
	o->value.barr.max_len = size;
	return o;
}

Object *create_arr_obj(Object *obj)
{
	Object *o = new_object(T_ARRAY);
	Object **data = (Object**)malloc(sizeof(Object*) * 100);
	o->value.arr.data = data;
	o->value.arr.max_len = 100;
	o->value.arr.data[0] = obj;
	o->value.arr.next_idx = 1;
	log("creating array object with object :%d %p %p\n", get_type(o), o, obj);
	return o;
}

Object *append_array_obj(Object *a, Object *o)
{
	Object **data;

	if (get_type(a) != T_ARRAY)
		return NULL;

	if (a->value.arr.max_len == a->value.arr.next_idx) {
		/*
		 * Allocate more memory to hold array elements
		 */
		data = (Object**)malloc(sizeof(Object*) *
				(a->value.arr.max_len + 100));
		memmove(data, a->value.arr.data, a->value.arr.max_len * sizeof(void*));
		free(a->value.arr.data);
		a->value.arr.data = data;
		a->value.arr.max_len = o->value.arr.max_len + 100;
	}
	a->value.arr.data[a->value.arr.next_idx++] = o;
	return a;
}

Object *from_int(Object *o, int type)
{
	char str[1024];

	switch (type) {
		case T_INT :
			return o;
		case T_CHAR :
			return create_char_obj(get_int(o) & 0xFF);
		case T_STRING :
			sprintf(str, "%ld", get_int(o));
			return create_str_obj(str);
		case T_FLOAT :
			return NULL;
	}
}

Object *from_char(Object *o, int type)
{
	char *str;
	unsigned char value;
	switch(type) {
		case T_INT :
			value = get_char(o);
			return create_int_obj(value);
		case T_CHAR :
			return NULL;
		case T_STRING :
			str = (char*)malloc(2);
			str[0] = get_char(o);
			str[1] = 0;
			return create_str_obj(str);
		default :
			return NULL;
	}	
	return NULL;
}


Object *from_string(Object *o, int type)
{
	unsigned long value;
	switch(type) {
		case T_INT :
			value = atoi(get_string(o));
			return create_int_obj(value);
		case T_STRING :
			return o;
		default :
			return NULL;
	}
	return NULL;
}

Object *from_float(Object *o, int type)
{
	switch(type) {
		case T_FLOAT :
			return o;
		default :
			return NULL;	
	}
	return NULL;
}

Object *from_barray(Object *o, int type)
{
	switch(type) {
		case T_BYTE_ARRAY : 
			return o;
		default :
			return NULL;
	}
	return NULL;
}

/* 
 * Convert a object into another object
 */
Object *convert_object(Object *o, int type)
{
	switch(get_type(o)) {
		case T_INT :
			return from_int(o, type);
		case T_CHAR :
			return from_char(o, type);
		case T_STRING :
			return from_string(o, type);
		case T_FLOAT :
			return from_float(o, type);
		case T_BYTE_ARRAY :
			return from_barray(o, type);
	}
	/* Invalid tyep specified */
	return NULL;
}

/*
 * This function promote an object from one type to another
 * CHAR -> INT -> FLOAT
 * STRING -> BYTE_ARRARY
 */
Object *promote(Object *a)
{
	switch(get_type(a)) {
		case T_CHAR :
			return create_int_obj(get_char(a));
		default :
			return NULL;
	}
	return NULL;
}

void print_object(Object *a)
{
	int i =0;

	if (a==NULL) {
		printf("NULL\n");
		return;
	}
	
	switch(get_type(a)) {
	case T_INT :
		printf("integer: %ld\n", get_int(a));
		break;
	case T_CHAR :
		printf("char :%c (%d)\n", (char)get_char(a), (char)get_char(a));
		break;
	case T_ARRAY :
		printf("Array [\n");
		for (i=0; i < a->value.arr.next_idx ; i++) 
			print_object(a->value.arr.data[i]);
		printf("]\n");
		break;
	case T_STRING :
		printf("string: %s\n", get_string(a));
		break;
	default :
		printf("non printable object");
		break;
	}
}

/* The array access functions */
Object *array_access(Object *o, Object *idx)
{
	int n, value;
	char *ptr;

	if (o == NULL || idx == NULL)
		return NULL;

	switch(get_type(o)) {
		case T_STRING :
		case T_BYTE_ARRAY :
			if (get_type(idx) != T_INT) {
				fprintf(stderr, "Invalid index specifiler");
				return NULL;
			}
			ptr = get_string(o);
			n = get_int(idx);
			value = *(ptr+n);
			return create_char_obj(value);
			break;
		case T_ARRAY :
			if (get_type(idx) != T_INT) {
				fprintf(stderr, "Invalid index specifiler");
				return NULL;
			}
			n = get_int(idx);
			if ( n >= o->value.arr.next_idx) {
				fprintf(stderr, "index out of bound %d\n", n);
				return NULL;
			}
			return o->value.arr.data[n];
		default :
			fprintf(stderr, "Array access can be possible only with "
				" string, bytearray and array type of objects");
			return NULL;
	}
	return NULL;	
}

/* The array access functions */
Object *array_range(Object *o, Object *idx1, Object *idx2)
{
	int n, i, value;
	int start, end;
	char *data;
	char *ptr;
	Object *obj;


	if (o == NULL || idx1 == NULL || idx2 == NULL)
		return NULL;

	switch(get_type(o)) {
		case T_STRING :
		case T_BYTE_ARRAY :
			if (get_type(idx1) != T_INT || get_type(idx2) != T_INT) {
				fprintf(stderr, "Invalid index specifiler");
				return NULL;
			}
			ptr = get_string(o);
			start = get_int(idx1);
			end = get_int(idx2);
			data = (char*)malloc(end - start +1);
			for (i=0, n = start; n <= end; n++, i++)
				data[i] = *(ptr+n);
			if (get_type(o) == T_STRING)
				return create_str_obj(data);
			else
				return create_barray_obj(data, end-start+1);
			break;
		case T_ARRAY :
			if (get_type(idx1) != T_INT || get_type(idx2) != T_INT) {
				fprintf(stderr, "Invalid index specifiler");
				return NULL;
			}
			start = get_int(idx1);
			end = get_int(idx2);
			if ( end >= o->value.arr.next_idx || start > end) {
				fprintf(stderr, "index out of bound %d\n", n);
				return NULL;
			}
			data = (Object*) malloc(sizeof(Object*) * (end - start + 1));
			obj = create_arr_obj(o->value.arr.data[start]);
			for (n = start +1; n <= end; n++)
				append_array_obj(obj, o->value.arr.data[n]);
			return obj;
			
		default :
			fprintf(stderr, "Array access can be possible only with "
				" string, bytearray and array type of objects");
			return NULL;
	}
	return NULL;	
}

