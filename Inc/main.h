
#ifndef STM32_MAIN
#define STM32_MAIN

extern int32_t  *stack_data;
extern uint32_t *stack_return;
extern uint8_t mode;


/* Public defines ------------------------------------------------------------*/
/* USER CODE BEGIN DEFINES */

/*WORD SPACE
*word structure: 
**4 bytes - next word adrress
**7 bytes - word name
**1 byte - flags
**4 bytes - execution token adress
*size - 24 KB total
*/
#define DATA_WORDS_BEGIN                ((void*)0x20028000)
#define DATA_WORDS_END                  ((void*)0x2002DFE0)

/*DATA STACK
*stack - up to 1024 elements, 4B each
*values - signed numbers of int32_t type
*size - 4KB total.
*/
#define STACK_DATA_BEGIN                ((int32_t*)0x2002E000)
#define STACK_DATA_END                  ((int32_t*)0x2002EFF0)

/*RETURN STACK
*return stack - the same as data stack
*but consists of unsigned numbers.
*size - 2KB total.
*/
#define STACK_RETURN_BEGIN              ((uint32_t*)0x2002F000)
#define STACK_RETURN_END                ((uint32_t*)0x2002F7F0)

/*STRING BUFFER
*size 1KB total
*/
#define STRING_BUFFER_BEGIN             ((char*)0x2002F800)
#define STRING_BUFFER_END               ((char*)0x2002FBFF)

/*USER MEM
*size 1KB total
*/
#define USER_MEM_BEGIN                  ((int32_t*)0x2002FC00)
#define USER_MEM_END                    ((int32_t*)0x2002FFFF)

enum forth_error_codes{
  ALL_OK = 0,
  DATA_STACK_OVERFLOW = 1,
  RETURN_STACK_OVERFLOW = 2,
  WORDS_SPACE_OVERFLOW = 3
};

#define WORD_MAX_LEN                    6    

/* USER CODE END DEFINES */


#endif