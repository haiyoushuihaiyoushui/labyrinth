#ifndef __LIST_STACK_H__
#define __LIST_STACK_H__

typedef struct stack_t
{
	int x;
	int y;
	struct stack_t *next;
}Stack_t,*List;

typedef struct head
{
	int count;
	List next;
}Head,*List_top;

List_top stack_create(void);
int push(List_top head,int x,int y);
int pop(List_top head,int *x,int *y);
int top(List_top s,int *x,int *y);
int stack_size(List_top s);
List_top reverse_stack(List_top stack);
void destroy_list(List_top head);

#endif
