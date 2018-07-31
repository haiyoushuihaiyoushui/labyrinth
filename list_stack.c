#include "list_stack.h"
#include "main.h"

#define ERROR -1
#define OK 0
	
List_top stack_create(void)
{
	List_top p = (List_top)malloc(sizeof(Head));
	assert(p);
	
	p->count = 0;
	p->next = NULL;
	
	return p;	
}

int push(List_top head,int x,int y)
{
	if (!head)	return ERROR;
	
	List node = (List)malloc(sizeof(Stack_t));
	assert(node);
	
	node->x = x;
	node->y = y;
	node->next = NULL;
	
	List p = head->next;
	head->next = node;
	node->next = p;

	head->count++;
	return OK;
}
	
int pop(List_top head,int *x,int *y)
{
	if (head->count == 0)	return ERROR;
	List q = head->next;
	
	*x = q->x;
	*y = q->y;

	List node = q->next;
	head->next = node;
	free(q);
	
	head->count--;
	return OK;
}

int top(List_top s,int *x,int *y)
{
	if (stack_size(s) != 0)
	{
		*x = s->next->x;
		*y = s->next->y;
		return OK;
	}
	else 	return ERROR;
}

int stack_size(List_top s)
{
	return s->count;
}

List_top reverse_stack(List_top stack)
{
	int x = 0;
	int y = 0;
	List_top tem_stack = stack_create();
	
	while (stack_size(stack) != 0)
	{
		pop(stack,&x,&y);
		push(tem_stack,x,y);
	}
	free(stack);
	
	return tem_stack;
}

void destroy_list(List_top head)
{
	int x = 0;
	int y = 0;
	
	while (stack_size(head) != 0)
	{
		pop(head,&x,&y);
	}
	
	free(head);
}
