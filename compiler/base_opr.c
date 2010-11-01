#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"

Object *add_int(Object *a, Object *b);
Object *sub_int(Object *a, Object *b);
Object *mult_int(Object *a, Object *b);
Object *div_int(Object *a, Object *b);
Object *cmp_int_le(Object *a, Object *b);
Object *cmp_int_gt(Object *a, Object *b);
Object *cmp_int_lt(Object *a, Object *b);
Object *cmp_int_eq(Object *a, Object *b);
Object *cmp_int_ge(Object *a, Object *b);
Object *append_str(Object *a, Object *b);
Object *cmp_str_eq(Object *a, Object *b);
Object *cmp_str_le(Object *a, Object *b);
Object *cmp_str_ge(Object *a, Object *b);
Object *cmp_str_lt(Object *a, Object *b);
Object *cmp_str_gt(Object *a, Object *b);
Object *mult_str_int(Object *s, Object *num);

struct basic_binary_operation_table {
	char *oper;
	int type1;
	int type2;
	function_ptr func;
} b_opr_tbl[] = {
	{ "+", T_INT, T_INT, add_int },
	{ "-", T_INT, T_INT, sub_int },
	{ "*", T_INT, T_INT, mult_int },
	{ "/", T_INT, T_INT, div_int },
	{ "<=", T_INT, T_INT, cmp_int_le },
	{ ">=", T_INT, T_INT, cmp_int_ge },
	{ "==", T_INT, T_INT, cmp_int_eq },
	{ "<", T_INT, T_INT, cmp_int_lt },
	{ ">", T_INT, T_INT, cmp_int_gt },
	{ "+", T_STRING, T_STRING, append_str },
	{ "==", T_STRING, T_STRING, cmp_str_eq },
	{ "<=", T_STRING, T_STRING, cmp_str_le },
	{ ">=", T_STRING, T_STRING, cmp_str_ge },
	{ "<", T_STRING, T_STRING, cmp_str_lt },
	{ ">", T_STRING, T_STRING, cmp_str_gt },
	{ "*", T_STRING, T_INT, mult_str_int },
};

Object *minus(Object *a)
{
	switch(get_type(a)) {
		case T_INT :
			return create_int_obj( -1 * get_int(a));
		case T_CHAR :
			return create_char_obj(-1 * get_char(a));
		default :
			return NULL;
	}
	return NULL;
}

Object *add_int(Object *a, Object *b)
{
	if (get_type(a) == T_INT && get_type(b) == T_INT)
		return create_int_obj(get_int(a) +
				      get_int(b));
	else 
		return NULL;
}

Object *sub_int(Object *a, Object *b)
{
	if (get_type(a) == T_INT && get_type(b) == T_INT)
		return create_int_obj(get_int(a) -
				      get_int(b));
	else 
		return NULL;
}

Object *mult_int(Object *a, Object *b)
{
	if (get_type(a) == T_INT && get_type(b) == T_INT)
		return create_int_obj(get_int(a) *
				      get_int(b));
	else 
		return NULL;
}

Object *div_int(Object *a, Object *b)
{
	if (get_type(a) == T_INT && get_type(b) == T_INT)
		return create_int_obj(get_int(a) /
				      get_int(b));
	else 
		return NULL;
}

Object *cmp_int_le(Object *a, Object *b)
{
	return create_int_obj(
		(get_int(a) <= get_int(b)) ? 1 : 0);
}

Object *cmp_int_gt(Object *a, Object *b)
{
	return create_int_obj(
		(get_int(a) > get_int(b))? 1 : 0);
}

Object *cmp_int_lt(Object *a, Object *b)
{
	return create_int_obj(
		(get_int(a) < get_int(b)) ? 1 : 0);
}

Object *cmp_int_eq(Object *a, Object *b)
{
	return create_int_obj(
		(get_int(a) == get_int(b))? 1 : 0);
}

Object *cmp_int_ge(Object *a, Object *b)
{
	return create_int_obj(
		(get_int(a) >= get_int(b)) ? 1 : 0);
}

Object *append_str(Object *a, Object *b)
{
	int size = strlen(get_string(a)) + strlen(get_string(b));
	char *str = (char*)malloc(size +1);
	strcpy(str, get_string(a));
	strcat(str, get_string(b));
	return create_str_obj(str);
}

Object *cmp_str_eq(Object *a, Object *b)
{
	return create_int_obj(
		(strcmp(get_string(a),
		       get_string(b)) == 0)? 1 : 0);
}

Object *cmp_str_le(Object *a, Object *b)
{
	return create_int_obj(
		(strcmp(get_string(a), get_string(b)) <= 0) ? 1 : 0);
}

Object *cmp_str_ge(Object *a, Object *b)
{
	return create_int_obj(
		(strcmp(get_string(a), get_string(b)) >= 0) ? 1 : 0);
}

Object *cmp_str_lt(Object *a, Object *b)
{
	return create_int_obj(
		(strcmp(get_string(a), get_string(b)) < 0) ? 1 : 0);
}

Object *cmp_str_gt(Object *a, Object *b)
{
	return create_int_obj(
		(strcmp(get_string(a), get_string(b)) > 0) ? 1 : 0);
}

Object *mult_str_int(Object *s, Object *num)
{
	int n = get_int(num);
	int len = strlen(get_string(s));
	int total_len = len * n + 1;
	char *str;
	char *instr = get_string(s);
	str = (char *)malloc(total_len);
	*str = 0;
	while (n--) {
		strcat(str, instr);
	}
	return create_str_obj(str);
}

Object *apply_operator(char *opr, Object *a, Object *b)
{
	int i =0;
	Object *o, *arg1, *arg2, *to_ret;

	if (a == NULL || b == NULL)
		return NULL;

	/* 
 	 * Check if matching operator found then return the result
 	 */
	for (i = 0;
		 i < sizeof(b_opr_tbl)/sizeof(struct basic_binary_operation_table);
		 i++) {
		if (strcmp(opr, b_opr_tbl[i].oper) == 0 &&
			get_type(a) == b_opr_tbl[i].type1 &&
			get_type(b) == b_opr_tbl[i].type2)
				return b_opr_tbl[i].func(a,b);
	}

	/*
 	 * convert one argument type (b) to another (a)
 	 */
	o = convert_object(b, get_type(a));
	to_ret = apply_operator(opr, a, o);
	/* Either o is NULL or no result */
	if (to_ret)
		return to_ret;

	/* Convert argument of type a to type b.
     */
	o = convert_object(a, get_type(b));
	to_ret = apply_operator(opr, o, b);

	if (to_ret)
		return to_ret;

	/* 
 	 * Conversion does not worked, not try promoting the
 	 * arguments.
 	 */
	o = promote(a);
	to_ret = apply_operator(opr, o, b);
	if (to_ret)
		return to_ret;
	
	o = promote(b);
	to_ret = apply_operator(opr, a, o);
	if (to_ret)
		return to_ret;

	return NULL;
}

