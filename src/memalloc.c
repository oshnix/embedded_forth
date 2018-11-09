#include "memalloc.h"

word* stack_mem(){
	return malloc(sizeof(word)*KB);
}

word* dictionary_mem(){
	return malloc(sizeof(word)*KB*20);
}

word* user_mem(){
	return malloc(sizeof(word)*KB);
}
word* return_stack(){
	return malloc(sizeof(word)*KB);
}

