#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define MAP01 "new.txt"		//修改该语句更换地图
#define CAN 1
#define CANNOT 0

#ifdef linux
	#define CLEAR "clear"
#elif WIN32
	#define CLEAR "cls"
#endif

#endif
