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
void word_end(void);
void read_word(void);
void find_word(void);
void lit(void);
void flag_check(void);
void exec(void);
void is_num(void);
void cycle_init(void);
void param_add(void);
/* USER CODE END PFP */

/* Private defines -----------------------------------------------------------*/
#define READ_XT         (void(*[1])()){read_word}
#define LIT_XT          (void(*[1])()){lit}
#define FIND_XT         (void(*[1])()){find_word}
#define EXEC_XT         (void(*[1])()){exec}
#define IS_NUM_XT       (void(*[1])()){is_num}
#define CYCLE_INIT      (void(*[1])()){cycle_init}
#define PARAM_ADD_XT    (void(*[1])()){param_add}
#define FLAG_CHECK_XT   (void(*[1])()){flag_check}

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
struct word_description *next_word_space = (struct word_description*)DATA_WORDS_BEGIN;
void (**next_xt_space)(void);
char end_docol = 1;
void(***current_xt)(void);
void(**current_word)(void);
void(*word_end_xt[1])() = {word_end};
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

uint8_t char_between(char current, char lower, char upper){
  return (lower <= current && current <= upper);
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
  current_xt = (void(***)())(*(stack_return--));
}
void lit(void){
    put((int32_t)(*(++current_xt)));
}
void put(int32_t new_number){
  *(++stack_data) = new_number;
}

void cycle_init(void){
  *(++stack_data) = (int32_t)mode;
  *(++stack_data) = (int32_t)STRING_BUFFER_BEGIN;
}

void flag_check(void){
  ++stack_data;
  *stack_data = (int32_t)*((char*)(*(stack_data-1)) - 1);
  
}

void param_add(void){
  *next_xt_space = (void(*)())(*(stack_data--));
  ++next_xt_space;
}

void read_word(void){
  scanf("%s", (char*)*stack_data);
  ++stack_data;
  *stack_data = strlen((char*)*(stack_data -1));
}

void exec(void){
  *(current_xt + 1) = (void(**)(void))*(stack_data--);
  --stack_data;
}

void find_word(void){
  if(!(*stack_data && *stack_data <= WORD_MAX_LEN)){
    *(++stack_data) = 0;
    return;
  }
  --stack_data;
  struct word_description *current_word = last_word;
    while(current_word != 0 && !(strcmp((char*)*(stack_data), current_word->name))){
      current_word = current_word->previous;
    }
    if(!current_word){
      *(++stack_data) = 0; 
    } else {
      *(++stack_data) = (int32_t)(current_word->xt);
    }
}

void is_num(void){
  int32_t value = 0;
  char* buf = (char*)(*stack_data);
  if(('-' == *buf && char_between(*(buf+1), '0', '9')) || char_between(*buf, '0', '9')){
    int8_t multiply = 1;
    if('-' == *buf){
      multiply = -1;
      ++buf;
    }
    while(char_between(*buf, '0', '9')){
      value = (value * 10) + ((*buf) - '0');
      ++buf;
    }
    value *= multiply;
    if(*buf){
      *(++stack_data) = 0;
    } else {
      *(stack_data++) = value;
      *(stack_data) = 1;
    }
  }
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
  *(next_xt_space++) = (void(*)(void))(word_end_xt);
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
  current_xt = (void(***)(void))(*current_xt);
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

void less(void){
  ++stack_data;
  *stack_data = (*(stack_data - 2) < *(stack_data - 1));
}

void mem(void){
  *(++stack_data) = (int32_t)USER_MEM_BEGIN;
}
         
void read(void){
  if(*stack_data >= (int32_t)USER_MEM_BEGIN && *stack_data <= (int32_t)USER_MEM_END - sizeof(int32_t*) + 1){
    *(stack_data) = *((int32_t*)(*stack_data));
  } else {
    printf("Wrong memory access\r\n");
  }
}

void write(void){
  if(*stack_data >= (int32_t)USER_MEM_BEGIN && *stack_data <= (int32_t)USER_MEM_END - sizeof(int32_t*) + 1){
    --stack_data;
    *((int32_t*)(*(stack_data + 1))) = *(stack_data);
    --stack_data;
  } else {
    printf("Wrong memory access\r\n");
  }
}

/*Not added in dictionary ----------------------------------------------------*/

/* USER CODE END EW*/ 



/* Embeded words storage -----------------------------------------------------*/ 
#define EMBEDDED_WORD_COUNT 23
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
  {&words[17], "<", 0, less},
  {&words[18], "mem", 0, mem},
  {&words[19], "@", 0, read},
  {&words[20], "!", 0, write},
  {&words[21], "read", 0, read_word},
};

#define MINUS_XT words[1].xt
#define BRANCH_XT words[16].xt
#define COND_BRANCH_XT words[17].xt
#define DROP_XT words[8].xt
#define ROT_XT words[15].xt


struct word_description *last_word = &(words[EMBEDDED_WORD_COUNT - 1]);

/*Initialize array with xt's for forth bootsrap loop -------------------------*/

 void(**interpretator_loop[LOOP_LENGTH])() = {
    CYCLE_INIT,
    READ_XT,
    ROT_XT,
    /*if mode == 1, continue, else - goto interpretator*/
    COND_BRANCH_XT,
    (void(**)()) 47,
      DROP_XT,
      FIND_XT,
      /*if input isn't word - goto, else - continue*/
      COND_BRANCH_XT,
      (void(**)())32,
        FLAG_CHECK_XT,
        LIT_XT,
        /*If flag == i, goto immediate execution*/
        (void(**)())'i',
        MINUS_XT,
        COND_BRANCH_XT,
          (void(**)())21,
        DROP_XT,
        FLAG_CHECK_XT,
        LIT_XT,
        /*If flag == r, read number from buffer and put it in word*/
        (void(**)())'r',
        MINUS_XT,
        COND_BRANCH_XT,
          (void(**)())5,
        DROP_XT,
        PARAM_ADD_XT,
        DROP_XT,
        BRANCH_XT,
        (void(**)()) -27,
      /*Part for r flag*/
      DROP_XT,
      PARAM_ADD_XT,
      READ_XT,
      DROP_XT,
      IS_NUM_XT,
      DROP_XT,
      PARAM_ADD_XT,
      BRANCH_XT,
      (void(**)()) -36,
      /*Part for i flag*/
      DROP_XT,
      EXEC_XT,
      (void(**)())0,
      BRANCH_XT,
      (void(**)()) -41,
      /*input isn't word*/
      DROP_XT,
      IS_NUM_XT,
      /*if not num - go to mistake output*/
      COND_BRANCH_XT,
      (void(**)()) 22,
        DROP_XT,
        LIT_XT,
        LIT_XT,
        PARAM_ADD_XT,
        PARAM_ADD_XT,
        BRANCH_XT,
        (void(**)()) -52,
    /*If mode == 0, we are in interpretator*/
    DROP_XT,
    FIND_XT,
    COND_BRANCH_XT,
    (void(**)())4,
      EXEC_XT,
      (void(**)())0,
      BRANCH_XT,
      (void(**)()) -60,
    DROP_XT,
    IS_NUM_XT,
    COND_BRANCH_XT,
    (void(**)())3,
      DROP_XT,
      BRANCH_XT,
      (void(**)()) -67,
    DROP_XT,
    BRANCH_XT,
    (void(**)()) -70,
  };
/* USER CODE END 0 */