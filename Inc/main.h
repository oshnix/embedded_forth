
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
#define DATA_WORDS_BEGIN                ((uint32_t*)0x2002A000)
#define DATA_WORDS_END                  ((uint32_t*)0x2002FFFF)

/*DATA STACK
*stack - up to 1024 elements, 4B each
*values - signed numbers of int32_t type
*size - 4KB total.
*/
#define STACK_DATA_BEGIN                ((int32_t*)0x20028000)
#define STACK_DATA_END                  ((int32_t*)0x20028FFF)

/*RETURN STACK
*return stack - the same as data stack
*but consists of unsigned numbers.
*size - 2KB total.
*/
#define STACK_RETURN_BEGIN              ((uint32_t*)0x20029000)
#define STACK_RETURN_END                ((uint32_t*)0x200297FF)

/*STRING BUFFER
*size 1KB total
*/
#define STRING_BUFFER_BEGIN             ((char*)0x20029800)
#define STRING_BUFFER_END               ((char*)0x20029BFF)

/*USER MEM
*size 1KB total
*/
#define USER_MEM_BEGIN                  ((int32_t*)0x20029C00)
#define USER_MEM_END                    ((int32_t*)0x2002FFFF)


#define WORD_MAX_LEN                    6    

/* USER CODE END DEFINES */


#endif