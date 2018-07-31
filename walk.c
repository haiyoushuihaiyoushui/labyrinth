#include "walk.h"
#include "map_operate.h"
#include "list_stack.h"
#include "main.h"

#define PASSED -1

int direction(List_top stack,int **p,int l,int w)
{
	int x = 0;
	int y = 0;
	int flag = CAN;
	Position cur;				
	Position over;
	Position start;
	start_search(p,l,w,&start);					//读取起点
	over_search(p,l,w,&over);					//读取终点
	memcpy(&cur,&start,sizeof(Position));
	
	print_map_step(p,cur,l,w);
	p[cur.y][cur.x] = PASSED;
	while (1)
	{
		if (memcmp(&cur,&over,sizeof(Position)) == 0)		//如果到终点则退出
			break;
		else 							//优先走没走过的路，若不存在则按原路返回直到存在为止
		{
			if (judge(stack,p,&cur,l,w) != 0)				
			{
				pop(stack,&x,&y);			//弹栈，cur原路返回	
				cur.x = x;
				cur.y = y;
				print_map_step(p,cur,l,w);
				if (memcmp(&cur,&start,sizeof(Position)) == 0)
				{
					flag = CANNOT;
					printf("该迷宫无从起点到终点的通路\n");
					break;
				}
			}
			else 	print_map_step(p,cur,l,w);
		}
	}
	push(stack,over.x,over.y);
	
	if (flag == CANNOT) 
		return CANNOT;
	else 	return CAN;
}


int judge(List_top stack,int **p,Position *cur,int l,int w)
{
	int x = 0;
	int y = 0;
	if (stack_size(stack) != 0)
		top(stack,&x,&y);
	
	if ((cur->y)-1 >= 0 && up(p,cur) == 0)				//压栈后，使cur向没走过的格子移一步
	{
		push(stack,cur->x,cur->y);				
		(cur->y)--;	
		p[cur->y][cur->x] = PASSED;
							
		return 0;
	}
	else if ((cur->x)+1 < l && right(p,cur) == 0)
	{
		push(stack,cur->x,cur->y);
		(cur->x)++;	
		p[cur->y][cur->x] = PASSED;
		
		return 0;
	}
	else if ((cur->y)+1 < w && down(p,cur) == 0)
	{
		push(stack,cur->x,cur->y);
		(cur->y)++;	
		p[cur->y][cur->x] = PASSED;
		
		return 0;
	}
	else if ((cur->x)-1 >= 0 && left(p,cur) == 0)
	{
		push(stack,cur->x,cur->y);
		(cur->x)--;	
		p[cur->y][cur->x] = PASSED;
		
		return 0;
	}
	
	else 	return 1;
}

