#ifndef STAB_PARSER_H_
#define STAB_PARSER_H_


#define MAX_STR_LEN (1024)
#define MAKEID(id1, id2) (id1 << 16 | id2)

struct stab_entry {
	unsigned char *str;
	int type;
	int other;
	int desc;
	int value;
	struct stab_entry *next;
};

typedef struct array_type {
	int start_index;
	int end_index;
} array_type_t;

typedef struct {
	char name[80];
} forward_ref_t;

typedef struct basic_type {
	int sign;
	int offset;
	int size;
	int bit_size;
} basic_type_t;

typedef struct float_type {
	int size;
}float_type_t;

struct type_info {
	int type; /* relation with parent type */ 
	int id; /* id constructed from two integers (id1, id2) */
	
	union {
		array_type_t atype;
		forward_ref_t reftype;
		basic_type_t btype;
		float_type_t ftype;
	}info;
	struct type_info *dep_type;
};

struct struct_member {
	char name[50];
	int offset;
	int size;
	struct type_info *type;
	struct struct_member *next;
};

enum member_type { 
	EQUAL,
	BASIC_TYPE,
	FLOAT_TYPE,
	POINTER,
	ARRAY,
	FUNCTION_PTR,
	VOLATILE,
	CONST,
	FORWARD_REF
};

enum struct_type {
	TYPE_STRUCTURE,
	TYPE_UNION
};


enum basic_types {
	VOID,
	UCHAR,
	CHAR,
	USHORT,
	SHORT,
	UINT,
	INT,
	ULONG,
	LONG,
	ULONG_LONG,
	LONG_LONG,
	TYPE_POINTER,
	TYPE_FUNCTION_PTR,
	TYPE_STRUCT,
	TYPE_BASIC_UNION,
	TYPE_ENUM,
	ERROR
};

	
struct struct_def {
	char name[80]; /* name of the structure defined */
	int id; /* id of the structure */
	int type; /* union or structure */
	unsigned int size;
	struct struct_member *members; /* list of structure members */
	struct struct_def *next;
};

struct type_def {
	char name[80]; /* name of typedef */
	int id; /* id of typedef */
	struct type_info *type;
	struct type_def *next;
};

#define TYPE_TABLE_SIZE	(2048)

#define ID_HASH(id) (((id >> 16) * (id & 0xFF)) % TYPE_TABLE_SIZE)

enum tentry_type {
	TYPE_INFO,
	TYPEDEF,
	STRUCTURE,
	UNION,
	ENUM
};

struct type_table_entry {
	int id;
	int type;
	union {
		struct type_info *ptr;
		struct struct_def *sdef;
		struct type_def *tdef;
	} info;
	struct type_table_entry *next;
};

typedef struct type_table_entry type_table_entry_t;

typedef struct type_hash {
	struct type_table_entry *head;
	struct type_table_entry *tail;
} type_hash_t;

struct forward_ref_table_entry {
	struct type_info *ptr;
	struct forward_ref_table_entry *next;
};

struct stab_namespace {
	char file_name[256];
	int id;
	type_hash_t *type_table;
	struct stab_namespace *next;
};

/* file scan functions */
char *scan_till(char *str ,char c);
int isletter(char ch);
char *scan_int(char *str, int *a);

void read_file(FILE*);
void parse_entry(char *str);


/* syntax scan functions */
void parse_type_defs(char *name, char *str);
void parse_struct_defs(char *name, char *str);
void parse_stab_entry(struct stab_entry *entry);
struct struct_member *parse_one_member(char **str);
char *member_type(char *str, struct type_info *mtype);
struct type_info *new_member_type();

/* data managemenet functions */
void add_stab_entry(struct stab_entry *entry);
void free_stab_entry_list();
void add_type_def(struct type_def *tdef);
void add_struct_def(struct struct_def *sdef);
struct struct_def* search_struct(char *name);
void add_to_forward_ref_table(struct type_info *tinfo);
void init_type_table();
void process_forward_refs();
int base_type(int id);

/* data print functions */
struct type_table_entry* new_type_table_entry();
void print_struct(struct struct_def *sdef, long long base, char *data);
int get_offset(struct struct_def *def, char *name);
int print_typedef(struct type_def *tdef, long long offset, char *data);
int print_struct_def(struct struct_def *sdef, long long offset, char *data);
int print_union(struct struct_def *def, long long offset, char *data);
int print_type_info(struct type_info *, long long offset ,char *data);
int print_id(int id, long long offset, char *data);

/* test functions */
void test_t_parser();
void test_s_parser(char *);
void print_stab_entry(struct stab_entry *entry);

#endif /*STAB_PARSER_H_*/
