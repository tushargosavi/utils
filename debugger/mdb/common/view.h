#ifndef VIEW_H
#define VIEW_H

struct view_data {
	char *data;
	unsigned long long addr;
	struct view_data *next;
};

struct view_entry {
	char name[33]; /* name of the view */
	int id;   /* id of type */
	int count;     /* number of entries in view */
	struct view_data *data_head;
	struct view_data *data_tail;
	struct view_entry *next_view;
};

#endif

