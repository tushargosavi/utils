#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_move_over(int a, int b);
void process_move_onto(int a, int b);
void process_pile_over(int a, int b);
void process_pile_into(int a, int b);

int num_blocks;

struct block {
  int occupied;
  int stack_head;
  int prev;
  int next;
};

struct block *blocks;

void init_blocks(int n)
{
  int i = 0;

  blocks = (struct block*)malloc(sizeof(struct block) * n);
  memset(blocks, 0, sizeof(struct block) * n);
  for (i=0; i < n; i++) {
    blocks[i].occupied = 1;
    blocks[i].next = -1;
    blocks[i].prev = -1;
    blocks[i].stack_head = i;
  }
}


/* Return blocks on top of specified block (a)
 * to their original positions
 */
void return_to_orig_pos(int a)
{
  int i, next;
  i = blocks[a].next;
  while (i != -1) {
    next = blocks[i].next;

    blocks[i].occupied = 1;
    blocks[i].next = -1;
    blocks[i].prev = -1;
    blocks[i].stack_head = i;

    i = next;
  }
  blocks[a].next = -1;
}

/* Add element 'b' on top of element 'a'
 */
void add_top(int a, int b)
{
  int i = b;
  int stack_head = blocks[a].stack_head;

  /* If b was any previous stack then make that stack end at
   * previous element of b, as b is going be part of next stack.
   */
  if (blocks[b].prev != -1)
    blocks[blocks[b].prev].next = -1;

  blocks[b].prev = a;
  blocks[b].occupied = 0;
  blocks[b].stack_head = stack_head;

  /* Change the stack for element on top of b */
  i = blocks[b].next;
  while (i != -1) {
    blocks[i].stack_head = stack_head;
    i = blocks[i].next;
  }
  blocks[a].next = b;
}

int stack_top(int a)
{
  int i = a;
  while (blocks[i].next != -1) i = blocks[i].next;
  return i;
}

void process_move_over(int a, int b)
{
  int i;
  return_to_orig_pos(a);
  i = stack_top(b);
  add_top(i, a);
}

void process_move_onto(int a, int b)
{ 
  return_to_orig_pos(a);
  return_to_orig_pos(b);
  add_top(b, a);
}

void process_pile_over(int a, int b)
{
  int top = stack_top(b);
  add_top(top, a);
}

void process_pile_onto(int a, int b)
{
  return_to_orig_pos(b);
  add_top(b, a);
}


process_command(char *command, int a, char *type, int b)
{

  /* If block a and block b are on same stack then neglate the command */  
  if (blocks[a].stack_head == blocks[b].stack_head) return;

  if (strcmp(command, "move")==0) {

    if (strcmp(type, "over") == 0)
      process_move_over(a, b);
    if (strcmp(type, "onto") == 0)
      process_move_onto(a, b);

  }
  if (strcmp(command, "pile") == 0) {
    if (strcmp(type, "over") == 0) 
      process_pile_over(a, b);
    if (strcmp(type, "onto") == 0) 
      process_pile_onto(a, b);
  }
  /* ignore the command */
}

void print_blocks_debug(int num_blocks)
{
  int i, j;
  for (i=0; i < num_blocks ; i++) {
    printf("%d: ", i);
    if (blocks[i].occupied) {
      printf("[%d %d %d %d]", i, blocks[i].next, blocks[i].prev, blocks[i].stack_head);
      j = blocks[i].next;
      while (j != -1) { 
     printf(" [%d %d %d %d]", j, blocks[j].next, blocks[j].prev, blocks[j].stack_head);
	j = blocks[j].next;
      }
    }    
    printf("\n");
  } 
}

void print_blocks(int num_blocks)
{
  int i, j;
  for (i=0; i < num_blocks ; i++) {
    printf("%d:", i);
    if (blocks[i].occupied) {
      printf(" %d", i);
      j = blocks[i].next;
      while (j != -1) { 
	printf(" %d", j);
	j = blocks[j].next;
      }
    }    
    printf("\n");
  } 
}

int main()
{
  char command[128], type[128];
  int a, b;

  scanf("%d", &num_blocks);
  init_blocks(num_blocks);
  do {
    scanf("%s", command);
    if (strcmp(command, "quit") == 0) break;
    else scanf("%d %s %d", &a, type, &b);
    process_command(command, a, type, b);
    /*
    sleep(2);
    printf("===========\n");
    print_blocks_debug(num_blocks);
    printf("===========\n");

    */
  } while (1);
  print_blocks(num_blocks);
  return 0;
}
