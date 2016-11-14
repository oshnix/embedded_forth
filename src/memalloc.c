#include "../include/memalloc.h"
#include <malloc.h>

#define KiloByte 0x100 /*0x100 * word = 1kB*/
/*
При реализации последующих функций вместо malloc будут использоваться абсолютные адреса ячеек памяти 
*/

word* stack_mem(){
	return malloc(sizeof(word)*KiloByte);
	/*При работе с памятью, все константы будут указаны в 16-ричной сс */
}

word* dictionary_mem(){
	return malloc(sizeof(word)*KiloByte*20);
}

word* user_mem(){
	return malloc(sizeof(word)*KiloByte);
}
word* return_stack(){
	return malloc(sizeof(word)*KiloByte);
}

