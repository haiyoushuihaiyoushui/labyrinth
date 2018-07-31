#include "produce_map.h"
#include "main.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define PASSED 0

Mazepoint *mazepoint_create(void)				//创建双向链表节点
{
	Mazepoint *p = (Mazepoint *)malloc(sizeof(Mazepoint));
	assert(p);
	
	p->x = 0;
	p->y = 0;
	p->next = NULL;
	p->last = NULL;
	
	return p;	
}
	
void destroy_double_list(Mazepoint *list)			//销毁双向链表
{
	if (list ==NULL)	return ;
	
	while (list->next != NULL)
	{
		list = list->next;
		free(list->last);
		list->last = NULL;
	}
	free(list);
}

int myrand(void)						//产生1到4的随机数
{
	return 1 + 4 * (double)rand() / RAND_MAX;
}

int get_count(int **p,Position cur,int l,int w)			//返回可以走的方向数		
{
	int count = 0;
	if (cur.x-2 > 0 && p[cur.y][(cur.x-2)] != PASSED)	//左
		count++;
	if (cur.x+2 < l && p[cur.y][(cur.x+2)] != PASSED)	//右
		count++;
	if (cur.y-2 > 0 && p[(cur.y-2)][cur.x] != PASSED)	//上
		count++;
	if (cur.y+2 < w && p[(cur.y+2)][cur.x] != PASSED)	//下
		count++;
	
	return count;
}
		
void new_map(int **p,int l,int w)
{
	int tem = 0;
	int flag = 0;
	int pointcount = (w+1)*(l+1) / 4 - 1;			//要遍历的次数	
	Position cur = {0,0};
	p[cur.y][cur.x] = PASSED;
	
	Mazepoint *q;
	Mazepoint *new_tail;
	Mazepoint *head = NULL;
	Mazepoint *tail = NULL;
	
	q = mazepoint_create();
	head = q;
	tail = q;

	while (pointcount != 0)
	{
		tem = myrand();
		flag = get_count(p,cur,l,w);
		
		if (flag != 0)		
		{
			new_tail = q;				//给链表的结尾赋值并插入新的尾节点，链表操作中‘=’表示指向同一地址
			q->x = cur.x;				
			q->y = cur.y;
			
			q = mazepoint_create();
			new_tail->next = q;
			q->last = new_tail;
			q->next = NULL;
			
			if (tem == LEFT && cur.x-2 >= 0 && p[cur.y][(cur.x-2)] != PASSED)
			{
				cur.x -= 2;
				p[cur.y][cur.x] = PASSED;
				p[cur.y][(cur.x+1)] = PASSED;
				--pointcount;
			}
			else if (tem == RIGHT && cur.x+2 < l && p[cur.y][(cur.x+2)] != PASSED)
			{
				cur.x += 2;
				p[cur.y][cur.x] = PASSED;
				p[cur.y][(cur.x-1)] = PASSED;
				--pointcount;
			}
			else if (tem == UP && cur.y-2 >= 0 && p[(cur.y-2)][cur.x] != PASSED)
			{
				cur.y -= 2;
				p[cur.y][cur.x] = PASSED;
				p[(cur.y+1)][cur.x] = PASSED;
				--pointcount;
			}
			else if (tem == DOWN && cur.y+2 < w && p[(cur.y+2)][cur.x] != PASSED)
			{
				cur.y += 2;
				p[cur.y][cur.x] = PASSED;
				p[(cur.y-1)][cur.x] = PASSED;
				--pointcount;
			}
			tail = q;
		}
		else
		{
			if (tail == head)
			{
				tail = head;
				return ;
			}
			else 					//尾节点回到上个节点
			{	
				tail = tail->last;		
				if (tail->last == NULL)
					tail = head;
				cur.x = tail->x;
				cur.y = tail->y;
			}
			
		}
	}
	destroy_double_list(head);
}

void save_map(int **p,int l,int w)				//将产生的地图加上墙壁存入文件
{
	int i = 0;
	int j = 0;
	FILE *pf = fopen(MAP01,"w");
	assert(pf);
	for (i=0; i<l+2; i++)
		fputc('1',pf);
	fputc('\n',pf);						//默认入口坐标为（0,1)
	fputc('0',pf);	
	
	for (i=0; i<w; i++)
	{
		if (i > 0)
			fputc('1',pf);
		for (j=0; j<l; j++)
		{
			if (p[i][j] == 0)
				fputc('0',pf);
			else if (p[i][j] == 1)
				fputc('1',pf);
		}
		if (i == w-1)
			fputc('0',pf);	
		else
			fputc('1',pf);
		fputc('\n',pf);
	}
	
	for (i=0; i<l+2; i++)
		fputc('1',pf);
	fputc('\n',pf);
		
	fclose(pf);
}
	
int **produce_map(void)
{
	int length = 0;
	int width = 0;
	int i = 0;
	int j = 0;
	
	while (1)
	{
		printf("请输入地图的长和宽(均为奇数):\n");
		scanf("%d%d",&length,&width);
		if (length == 0 || width == 0)
			continue;
		if ((length>=3 && length<=39) && (width>=3 && width<=39) && length%2==1 && width%2==1)		//限定输入
		{
			length -= 2;
			width -= 2;
			break;
		}
		else 	printf("\033[44;33m输入不符合要求，请重新输入\033[0m\n");
	}
	
	int **p = (int **)malloc(width*sizeof(int *));
	assert(p);
	for (i=0; i<width; i++)
	{
		p[i] = (int *)malloc(length*sizeof(int));
		assert(p[i]);
	}
	for (i=0; i<width; i++)				//初始化为1
	{
		for (j=0; j<length; j++)
		{
			p[i][j] = 1;
		}
	}
			
	new_map(p,length,width);		
	save_map(p,length,width);

	return p;
}	
