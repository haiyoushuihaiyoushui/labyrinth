#ifndef __WALK_H__
#define __WALK_H__

#include "list_stack.h"
#include "map_operate.h"

#define up(p,t) p[(t->y-1)][t->x]
#define down(p,t) p[(t->y+1)][t->x]
#define left(p,t) p[t->y][(t->x-1)]
#define right(p,t) p[t->y][(t->x+1)]

int judge(List_top stack,int **p,Position *cur,int l,int w);
int direction(List_top stack,int **p,int l,int w);

#endif
