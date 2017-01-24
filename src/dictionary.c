/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
#include "main.h"
#include "dictionary.h"
/* USER CODE END Includes */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void lowercase(char *src);
uint8_t strcmp(char *first, char* second);
void strcpy(char *src, char* dest);
uint16_t strlen(char *string);
void docol(void);
void word_end(void);
void read_word(void);
void find_word(void);
void lit(void);
void flag_check(void);
void exec(void);
void is_num(void);
void cycle_init(void);
void put(int32_t new_number);
void param_add(void);
void new_data(void);
void set_compilation_mode_on(void);
void set_compilation_mode_off(void);
void get_next_xt(void);
void set_new_word_space(void);
/* USER CODE END PFP */

/* Private defines -----------------------------------------------------------*/
#define READ_XT         (void(*[1])()){read_word}
#define WORD_END_XT     (void(*[1])()){word_end}
#define LIT_XT          (void(*[1])()){lit}
#define FIND_XT         (void(*[1])()){find_word}
#define SHIFT_NEXT      (void(*[1])()){set_new_word_space}
#define EXEC_XT         (void(*[1])()){exec}
#define GET_NEXT_XT     (void(*[1])()){get_next_xt}
#define COMPILE_XT      (void(*[1])()){set_compilation_mode_on}
#define END_COMPILE_XT  (void(*[1])()){set_compilation_mode_off}
#define CREATE_XT       (void(*[1])()){new_data}
#define IS_NUM_XT       (void(*[1])()){is_num}
#define CYCLE_INIT      (void(*[1])()){cycle_init}
#define FLAG_CHECK_XT   (void(*[1])()){flag_check}

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
struct colon_word *next_word_space = (struct colon_word*)DATA_WORDS_BEGIN;
void (**next_xt_space)(void);
char end_docol = 1;
void(***current_xt)(void);
void(**current_word)(void);
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

/**
*@brief:        count string length
*@param:        char *string - zero terminated string
*@retval:       uint16_t len - string length.
*/
uint16_t strlen(char *string){
  uint16_t count = 0;
  while(*(string++)) ++count;
  return count;
}

/**
*@brief:        checks if char between two others
*@param:        char current - char to check
                char lower - char that must be below or equal than current
                char upper - char that must be above or equal than current
*@retval:       uint8_t check - check result. 0 if false, else - 1 .
*/
uint8_t char_between(char current, char lower, char upper){
  return (lower <= current && current <= upper);
}

/**
*@brief:        copy string to another destination
*@param:        char *src- zero terminated string to copy
                char *dest - pointer to space where we need to copy string to
*@retval:       none.
*/
void strcpy(char *src, char* dest){
  while(*(dest++) = *(src++));
}


#define UPPER_TO_LOWER 'A' - 'a'
/**
*@brief:        translate all upper letters to lower
*@param:        char *src- zero terminated string to transform
*@retval:       none.
*/
void lowercase(char *src){
  while(*src){
    if('A' <= *src && 'Z' >= *src) *src -= UPPER_TO_LOWER;
    ++src;
  }
}

/* USER CODE END RF*/

/* Words without dictionary record --------------------------------------------*/
/* USER CODE BEGIN WWDR*/

/*restore current_xt*/
void word_end(){
  current_xt = (void(***)())(*(stack_return--));
}
/*increment current_xt and put value from it to stack*/
void lit(void){
    put((int32_t)(*(++current_xt)));
}
/*put value to stack*/
void put(int32_t new_number){
  *(++stack_data) = new_number;
}
/*gets pointer to next word during compilation and increment it*/
void get_next_xt(void){
  *(++stack_data) = (int32_t)next_xt_space;
  ++next_xt_space;
}
/* set forth mode to compile*/
void set_compilation_mode_on(void){
  mode = 1;
}
/* set forth mode to interpretate*/
void set_compilation_mode_off(void){
  mode = 0;
}
/*put flag and name from stack values 
and create a new word record. shifts next_xt to first xt
after word info*/
void new_data(void){
  next_word_space->previous = last_word;
  last_word = next_word_space;
  strcpy((char*)*(stack_data--), last_word->name);
  last_word->flag = (char)*(stack_data--);
  next_xt_space = last_word->xt;
}
/*put current mode and buffer pointer to stack*/
void cycle_init(void){
  *(++stack_data) = (int32_t)mode;
  *(++stack_data) = (int32_t)STRING_BUFFER_BEGIN;
}

/*put word's flag, whose xt currently on stack, on stack*/
void flag_check(void){
  ++stack_data;
  *stack_data = (int32_t)*((char*)(*(stack_data-1)) - 1);
}

/*shifts next_word_space to next_xt space
uses after finishing word compilation*/
void set_new_word_space(void){
  next_word_space = (struct colon_word*)next_xt_space;
}

/*read from stdin string, put it by adress in stack 
and put input length to stack*/
void read_word(void){
  scanf("%s", (char*)*stack_data);
  ++stack_data;
  *stack_data = strlen((char*)*(stack_data -1));
}
/*get xt from stack and put it next to current_xt*/
void exec(void){
  *(current_xt + 1) = (void(**)(void))*(stack_data--);
  --stack_data;
}
/* trying to find word, whose name is on stack and if succesfull - put 
it xt on stack*/
void find_word(void){
  if(!(*stack_data && *stack_data <= WORD_MAX_LEN)){
    *(++stack_data) = 0;
    return;
  }
  --stack_data;
  struct colon_word *current_word = last_word;
    while(current_word != 0 && !(strcmp((char*)*(stack_data), current_word->name))){
      current_word = current_word->previous;
    }
    if(!current_word){
      *(++stack_data) = 0; 
    } else {
      *(++stack_data) = (int32_t)(current_word->xt);
    }
}
/*check if value is num*/
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
    *(stack_data) = *((int32_t*)(*stack_data));
}

void write(void){
  --stack_data;
  *((int32_t*)(*(stack_data + 1))) = *(stack_data);
  --stack_data;
}
/* USER CODE END EW*/ 

/* Embeded words storage -----------------------------------------------------*/ 
#define EMBEDDED_WORD_COUNT 21
struct colon_word words[EMBEDDED_WORD_COUNT] = {
  {0, "+", 0, add},
  {&words[0], "-", 0, sub},
  {&words[1], ".s", 0, print_all},
  {&words[2], "*", 0, mul},
  {&words[3], "/", 0, div},
  {&words[4], "!", 0, write},
  {&words[5], "read", 0, read_word},
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
};

#define MINUS_XT        words[1].xt
#define WRITE_MEM_XT    words[5].xt
#define BRANCH_XT       words[16].xt
#define COND_BRANCH_XT  words[17].xt
#define DROP_XT         words[8].xt
#define ROT_XT          words[15].xt


struct word_put_xt put_info = {&(words[EMBEDDED_WORD_COUNT - 1]),
      "putxt", 0, docol,
      {GET_NEXT_XT, WRITE_MEM_XT, WORD_END_XT}};

#define PUT_XT          put_info.doc

struct word_begin_compilation begin_info = {&put_info, 
      ":", 0, docol,
      {LIT_XT, (void(**)())0, 
      LIT_XT, (void(**)())STRING_BUFFER_BEGIN, 
      READ_XT, DROP_XT, CREATE_XT, COMPILE_XT,
      LIT_XT, (void(**)())docol,
      PUT_XT, WORD_END_XT}};

struct word_end_compilation end_info = { &begin_info,
      ";", 'i', docol,
      {END_COMPILE_XT ,LIT_XT, WORD_END_XT,
      PUT_XT, SHIFT_NEXT, WORD_END_XT}
  
};

struct colon_word *last_word = (struct colon_word*)(&end_info);

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
        PUT_XT,
        DROP_XT,
        BRANCH_XT,
        (void(**)()) -27,
      /*Part for r flag*/
      DROP_XT,
      PUT_XT,
      READ_XT,
      DROP_XT,
      IS_NUM_XT,
      DROP_XT,
      PUT_XT,
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
        PUT_XT,
        PUT_XT,
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
