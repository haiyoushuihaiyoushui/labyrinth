#include "main.h"
#include "list_stack.h"
#include "map_operate.h"
#include "walk.h"
#include "produce_map.h"

int main(void)
{
#ifdef WIN32
	system("chcp 65001");
#endif
	srand(time(0));
	int i = 0;
	int width = 0;
	int length = 0;
	int step = 0;
	int flag = 0;
	char choice[2] = "";
	int **p = produce_map();					//产生随机地图
	p = read_map(&length,&width);					//读取随机地图
	
	List_top stack = stack_create();
	flag = direction(stack,p,length,width);
	
	if (flag == CAN)
	{
		while (1)
		{
			printf("请选择按不重复路径行走（w)或退出（q)：\n");
			scanf("%s",choice);
			if (strcmp(choice,"q") == 0)
				return 0;
			else if (strcmp(choice,"w") == 0)
				break;
			else 	printf("\033[46;31m没有这个选项，请重新输入\033[0m\n");
		}
		
		stack = reverse_stack(stack);
		step = stack_size(stack) - 1;
		
		print_map_stack(p,stack,length,width);
		printf("无重复路径共走了%d步\n",step);
	}
	
	destroy_list(stack);
	for (i=0; i<width; i++)
		free(p[i]);
	free(p);
		
	return 0;
}
