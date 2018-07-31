#ifndef __MAP_OPERATE_H__
#define __MAP_OPERATE_H__

#include "list_stack.h"

typedef struct position
{
	int x;
	int y;
}Position;

int **read_map(int *length,int *width);
void print_map_step(int **p,Position cur,int l,int w);
void print_map_stack(int **p,List_top stack,int l,int w);
void start_search(int **p,int l,int w,Position *start);
void over_search(int **p,int l,int w,Position *over);

#endif
