#ifndef NODE_H
#define NODE_H

enum nodeEnum {
	typeIntConst,
	typeChrConst,
	typeStrConst,
	typeArray,
	typeID,
	typeOpr
};

struct constNode {
	int type;
	union {
		unsigned long value;
		char *str;
	};
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
		struct oprNode		opr;
		struct arrNode		arr;
	};
} node_t;

#endif
