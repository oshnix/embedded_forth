/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */

#include "main.h"
#include "dictionary.h"

/* USER CODE END Includes */

/* USER CODE BEGIN 0 */


/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

void docol(void);
void end_adding(void);
void word_end();
/* USER CODE END PFP */


/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
struct word_description *next_word_space = (struct word_description*)DATA_WORDS_BEGIN;
void (**next_xt_space)(void);
char end_docol = 1;
void(**current_word)(void);
void(***current_xt)(void);
void(*word_ending[1])() = {word_end};
void(*word_lit[1])(void) ={lit};
/* USER CODE END PV */


/* Routine functions ----------------------------------------------------------*/
/* USER CODE BEGIN RF*/

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

uint16_t strlen(char *string){
  uint16_t count = 0;
  while(*(string++)) ++count;
  return count;
}

void strcpy(char *src, char* dest){
  while(*(dest++) = *(src++));
}

#define UPPER_TO_LOWER 'A' - 'a'
void lowercase(char *src){
  while(*src){
    if('A' <= *src && 'Z' >= *src) *src -= UPPER_TO_LOWER;
    ++src;
  }
}

/**
*@brief:        return max of two signed values
*@param:        int32_t a, b - two numbers to compare
*@retval:       a if a greater or equal b, else return b.
*/
int32_t max(int32_t a, int32_t b){
  return a >= b ? a : b;
}

/* USER CODE END RF*/

/* Words without dictionary record --------------------------------------------*/
/* USER CODE BEGIN WWDR*/

void word_end(){
  end_docol = 0;
}
void lit(void){
    put((int32_t)(*(++current_xt)));
}
void put(int32_t new_number){
  *(++stack_data) = new_number;
}
/* USER CODE END WWDR*/

/* Embedded Words ------------------------------------------------------------*/
/* USER CODE BEGIN EW*/ 

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

void dup(void){
  ++stack_data;
  *stack_data = *(stack_data - 1);
}

void drop(void){
  --stack_data;
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

void print_and_drop(){
  printf("%d\r\n", *stack_data);
  drop();
}

void equal(void){
  ++stack_data;
  *stack_data = (*(stack_data - 1) == *(stack_data -2));
}

void greater(void){
  ++stack_data;
  *stack_data = (*(stack_data - 2) > *(stack_data - 1));
}

void swap(void){
  int32_t tmp = *stack_data;
  *stack_data = *(stack_data - 1);
  *(stack_data - 1) = tmp;
}

void rotate(void){
  int32_t tmp = *(stack_data - 1);
  *(stack_data - 1) = *stack_data;
  *stack_data = *(stack_data -2);
  *(stack_data -2) = tmp;
}

void and(void){
  --stack_data;
  *stack_data &= *(stack_data + 1);
}

void not(void){
  *stack_data = *stack_data ? 0 : 1;
}

void jump(void){
  int32_t len = (int32_t)*(++current_xt);
  current_xt += len;
}

void cond_jump(void){
  if(!*stack_data) jump();
  else ++current_xt;
}

/*Not added in dictionary ----------------------------------------------------*/



/* USER CODE END EW*/ 

/* Embeded words storage -----------------------------------------------------*/ 
#define EMBEDDED_WORD_COUNT 18
struct word_description words[EMBEDDED_WORD_COUNT] = {
  {0, "+", 0, add},
  {&words[0], "-", 0, sub},
  {&words[1], ".s", 0, print_all},
  {&words[2], "*", 0, mul},
  {&words[3], "/", 0, div},
  {&words[4], ":", 0, new_word},
  {&words[5], ";", 'i', end_adding},
  {&words[6], "dup", 0, dup},
  {&words[7], "drop", 0, drop},
  {&words[8], ".", 0, print_and_drop},
  {&words[9], "=", 0, equal},
  {&words[10], ">", 0, greater},
  {&words[11], "swap", 0, swap},
  {&words[12], "and", 0, and},
  {&words[13], "not", 0, not},
  {&words[14], "rot", 0, rotate},
  {&words[15], "br", 'r', jump},
  {&words[16], "br0", 'r', cond_jump},
};
struct word_description *last_word = &(words[EMBEDDED_WORD_COUNT - 1]);

/* USER CODE END 0 */