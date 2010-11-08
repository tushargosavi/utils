#ifndef NODE_H
#define NODE_H

enum nodeEnum {
	typeIntConst,
	typeChrConst,
	typeStrConst,
	typeArray,
	typeID,
	typeOpr,
	typeFuncCall
};

struct constNode {
	int type;
	union {
		unsigned long value;
		char *str;
	};
};

struct funcNode {
	char *name;
	struct node *arg;
};

struct idNode {
	char *name;
};

struct oprNode {
	int oper;
	int nops;
	struct node *op[6];
};

struct arrNode {
	struct node *value;
};

typedef struct node {
	int type;
	union {
		struct constNode	con;
		struct idNode		id;
		struct arrNode		arr;
		struct funcNode		func;
		struct oprNode		opr;
	};
} node_t;

enum operations {
	ARRAY_SET = 100000
};

#endif
