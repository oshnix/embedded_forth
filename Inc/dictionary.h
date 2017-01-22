
#ifndef STM32_DICTIONARY
#define STM32_DICTIONARY

struct word_description{
  struct word_description *previous;
  char name[7];
  char flag;
  void(*xt[1])();
};

  
#define LOOP_LENGTH 51

/* Public variables definitions ----------------------------------------------*/
/* USER CODE PV BEGIN */
extern struct word_description *last_word;
extern void(**interpretator_loop[LOOP_LENGTH])();
extern void(**test_xt[5])();
extern void(***current_xt)(void);
extern void(**current_word)(void);
extern void (**next_xt_space)(void);
/* USER CODE PV END */

/* Public functions prototypes -----------------------------------------------*/
/* USER CODE PF BEGIN */
int32_t max(int32_t a, int32_t b);
void creater_sudo();
void interpretator_init(void);
void lowercase(char *src);
uint8_t strcmp(char *first, char* second);
void put(int32_t new_number);
void strcpy(char *src, char* dest);
uint16_t strlen(char *string);
/* USER CODE PF END */
#endif