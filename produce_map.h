#ifndef __PRODUCE_MAP_H__
#define __PRODUCE_MAP_H__

#include "map_operate.h"

typedef struct mazepoint
{
	int x;
	int y;
	struct mazepoint *next;
	struct mazepoint *last;
}Mazepoint;

Mazepoint *mazepoint_create(void);
void destroy_double_list(Mazepoint *list);
int myrand(void);
int get_count(int **p,Position cur,int l,int w)	;
void new_map(int **p,int l,int w);
void save_map(int **p,int l,int w);
int **produce_map(void);

#endif
