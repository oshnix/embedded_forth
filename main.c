#include <stdio.h>
//#include "memalloc.h"


int main(){
	register word *stack_top = stack_mem();
	word* dict_mem = dictionary_mem();
	word* user_mem = user_mem();
	word* return_top = return_stack();
	//printf("Size is: %d\n",sizeof(int*));
	
	return 0;
}









