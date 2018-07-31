#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <assert.h>

#ifdef linux
	#define CLEAR "clear"
#elif WIN32
	#define CLEAR "cls"
#endif

int main(void)
{
	FILE *pf = fopen("zzzz.txt","w");
	assert(pf);
	
	fclose(pf);
//	while (1);
	return 0;
}