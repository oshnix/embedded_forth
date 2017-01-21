/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */

#include "main.h"
#include "dictionary.h"

/* USER CODE END Includes */

/* USER CODE BEGIN 0 */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
struct word_description *next_word_space = (struct word_description*)DATA_WORDS_BEGIN;

void (**next_xt_space)(void);
char end_docol = 1;
void(**current_word)(void);
void(***current_xt)(void);
/* USER CODE END PV */

void docol(void);
void end_adding(void);
void word_end();

void(*word_ending[1])() = {word_end};

void add(void){
  --stack_data;
  *stack_data += *(stack_data + 1);
}

void sub(void){
  --stack_data;
  *stack_data -= *(stack_data + 1);
}

void mul(void){
  -- stack_data;
  *stack_data *= *(stack_data+1);
}
  
void div(void){
  --stack_data;
  *stack_data /= *(stack_data+1);
}

void new_word(void){
  scanf("%s", buffer);
  uint16_t len = strlen(buffer);
  if(!(len > 0 && len <= WORD_MAX_LEN)){
    printf("Wrong word name\r\n");
    return;
  }
  next_word_space->previous = last_word;
  last_word = next_word_space;
  strcpy(buffer, last_word->name);
  last_word->flag = 0;
  last_word->num_used = 0;
  last_word->xt[0] = docol;
  mode = 1;
  next_xt_space = (last_word->xt) + 1;
}

void end_adding(void){
  mode = 0;
  *(next_xt_space++) = (void(*)(void))(word_ending);
  next_word_space = (struct word_description*)next_xt_space;
}

void print_all(void){
  int32_t *data_pointer = stack_data;
  while(data_pointer >= STACK_DATA_BEGIN){
    printf("%d ", *data_pointer);
    --data_pointer;
  }
  printf("\r\n");
}

void docol(void){
  *(++stack_return) = (uint32_t)current_xt;
  current_xt = (void(***)(void))((current_word + 1));
  while(end_docol){
    current_word = *current_xt;
    (*current_word)();
    ++current_xt;
  }
  end_docol = 1;
  current_xt = (void(***)(void))(*(stack_return--));
}

void word_end(){
  end_docol = 0;
}



/**
*@brief:        compare two strings
*@param:        char *first, second - zero terminated strings to compare
*@retval:       1 if strings are equal, else - 0.
*/
uint8_t strcmp(char *first, char* second){
  while(*first == *second && *first){
    ++first;
    ++second;
  }
  return *first == *second ? 1 : 0;
}

/**
*@brief:        return max of two signed values
*@param:        int32_t a, b - two numbers to compare
*@retval:       a if a greater or equal b, else return b.
*/
int32_t max(int32_t a, int32_t b){
  return a >= b ? a : b;
}


void print(){
  
}

void print_and_drop(){
  
}

void lit(void){
    put((int32_t)(++current_word));
}


void put(int32_t new_number){
  *(++stack_data) = new_number;
}

uint16_t strlen(char *string){
  uint16_t count = 0;
  while(*(string++)) ++count;
  return count;
}

void strcpy(char *src, char* dest){
  while(*(dest++) = *(src++));
}

#define EMBEDDED_WORD_COUNT 8

struct word_description words[EMBEDDED_WORD_COUNT] = {
  {0, "+", 0, 2, add},
  {&words[0], "-", 0, 2, sub},
  {&words[1], ".s", 0, 0, print_all},
  {&words[2], "*", 0, 2, mul},
  {&words[3], "/", 0, 2, div},
  {&words[4], ":", 0, 0 ,new_word},
  {&words[5], ";", 'i', 0 ,end_adding},
  {&words[6], "", 0, 0 , word_end}
};

struct word_description *last_word = &(words[EMBEDDED_WORD_COUNT - 1]);
/* USER CODE END 0 */