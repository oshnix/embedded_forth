
#ifndef STM32_DICTIONARY
#define STM32_DICTIONARY

struct word_description{
  struct word_description *previous;
  char name[6];
  uint8_t num_used;
  uint8_t flag;
  void(*xt[1])();
};

extern struct word_description *last_word;
//extern void *next_xt_space;
uint8_t strcmp(char *first, char* second);
void put(int32_t new_number);
void strcpy(char *src, char* dest);
uint16_t strlen(char *string);

#endif