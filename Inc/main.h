
#ifndef STM32_MAIN
#define STM32_MAIN

extern uint32_t *next_xt;
extern int32_t  *stack_data;
extern uint32_t *stack_return;
extern uint32_t *stack_variables;
extern uint8_t mode;
extern char *buffer;
extern int32_t current_data;


/* Public defines ------------------------------------------------------------*/
/* USER CODE BEGIN DEFINES */

/*WORD SPACE
*word structure: 
**4 bytes - next word adrress
**7 bytes - word name
**1 byte - flags
**4 bytes - execution token adress
*size - 16 KB total
*/
#define DATA_WORDS_BEGIN                ((uint32_t*)0x20028000)
#define DATA_WORDS_END                  ((uint32_t*)0x2002BFFF)

/*DATA STACK
*stack - up to 1024 elements, 4B each
*values - signed numbers of int32_t type
*size - 4KB total.
*/
#define STACK_DATA_BEGIN                ((int32_t*)0x2002C000)
#define STACK_DATA_END                  ((int32_t*)0x2002CFFF)

/*RETURN STACK
*return stack - the same as data stack
*but consists of unsigned numbers.
*size - 4KB total.
*/
#define STACK_RETURN_BEGIN              ((uint32_t*)0x2002D000)
#define STACK_RETURN_END                ((uint32_t*)0x2002DFFF)

/*USER VARIABLES SPACE
*variable structure:
**4 byte - next variable adress
**4 byte - variable name
**4 byte - variable 
*size - 6KB total.
*/
#define DATA_VARIABLES_BEGIN            ((uint32_t*)0x2002E000)
#define DATA_VARIABLES_END              ((uint32_t*)0x2002F7FF)

#define STRING_BUFFER_BEGIN             ((char*)0x2002F800)
#define STRING_BUFFER_END               ((char*)0x2002FBFF)

#define USER_MEM_BEGIN                  ((int32_t*)0x2002FC00)
#define USER_MEM_END                    ((int32_t*)0x2002FFFF)


#define WORD_MAX_LEN                    6    

/* USER CODE END DEFINES */


#endif