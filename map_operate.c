#include "map_operate.h"
#include "list_stack.h"
#include "main.h"

#ifdef WIN32
	#include <windows.h>
	#define MYSLEEP	Sleep
	#define MYTIME	200
#elif linux
	#include <unistd.h>
	#define MYSLEEP	usleep
	#define MYTIME	200000
#endif

int **read_map(int *length,int *width)
{
	FILE *pf = fopen(MAP01,"r");
	assert(pf);
	
	int i = 0;
	int j = 0;
	int flag = 0;
	int ch = 0;
	
	while ((ch = fgetc(pf)) != EOF)
	{
		if (flag != 1)
			(*length)++;
		if (ch == '\n')
		{
			(*width)++;
			flag = 1;
		}
	}
	rewind(pf);
	printf("%d %d\n", *width, *length);
	int **p = (int **)malloc((*width)*sizeof(int *));
	assert(p);
	
	for (i=0; i<*width; i++)
	{
		p[i] = (int *)malloc((*length-1)*sizeof(int));
		assert(p[i]);
	}

	for (i=0; i<*width; i++)
	{
		for (j=0; j<*length; j++)
		{
			ch = fgetc(pf);
			if (ch != '\n')
			{
				if (ch == '0')
					p[i][j] = 0;
				else
					p[i][j] = 1;
			}
			else 	continue;
		}
	}
	(*length)--;
	
	fclose(pf);
	return p;
}

void print_map_stack(int **p,List_top stack,int l,int w)
{
	int x = 0;
	int y = 0;
	Position cur;
	while (stack_size(stack) != 0)
	{
		pop(stack,&x,&y);
		cur.x = x;
		cur.y = y;
		print_map_step(p,cur,l,w);
	}
}	
	
void print_map_step(int **p,Position cur,int l,int w)
{
	int i = 0;
	int j = 0;
	system(CLEAR);
	for (i=0; i<w; i++)
	{
		for (j=0; j<l; j++)
		{
			if (j == cur.x && i == cur.y)
			{
				printf("\033[41;31m%s\033[0m","  ");
				continue;
			}
			
			if (p[i][j] <= 0)
				printf("\033[47;37m%s\033[0m","  ");
			else
				printf("\033[40;30m%s\033[0m","  ");
		}
		printf("\n");
	}
//	getchar();
	MYSLEEP(MYTIME);
}
void start_search(int **p,int l,int w,Position *start)		//从地图左边界或上边界寻找入口
{
	int i = 0;
	
	for (i=0; i<l; i++)					//y不变x增加
	{
		if (p[0][i] == 0)
		{
			start->x = i;
			start->y = 0;
		}
	}
	
	for (i=0; i<w; i++)					//x不变y增加
	{
		if (p[i][0] == 0)
		{
			start->x = 0;
			start->y = i;
		}
	}
}

void over_search(int **p,int l,int w,Position *over)		//从地图下边界或右边界寻找出口
{
	int i = 0;
	
	for (i=0; i<w; i++)				
	{
		if (p[i][l-1] == 0)
		{
			over->x = l-1;
			over->y = i;
		}
	}
	
	for (i=0; i<l; i++)
	{
		if (p[w-1][i] == 0)
		{
			over->x = i;
			over->y = w-1;
		}
	}
}

