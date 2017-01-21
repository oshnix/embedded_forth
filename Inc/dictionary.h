
#ifndef STM32_DICTIONARY
#define STM32_DICTIONARY

struct word_description{
  struct word_description *previous;
  char name[6];
  char flag;
  uint8_t num_used;
  void(*xt[1])();
};

extern struct word_description *last_word;
extern void(**current_word)(void);
void lit(void);
int32_t max(int32_t a, int32_t b);
void creater_sudo();
void lowercase(char *src);
extern void (**next_xt_space)(void);
uint8_t strcmp(char *first, char* second);
void put(int32_t new_number);
void strcpy(char *src, char* dest);
uint16_t strlen(char *string);

#endif