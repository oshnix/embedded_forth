
#ifndef STM32_DICTIONARY
#define STM32_DICTIONARY

struct word_description{
  struct word_description *previous;
  char *name;
  uint8_t flag;
  void(*xt)();
};

extern struct word_description *last_word;
uint8_t strcmp(char *first, char* second);
void add(void);
void put(int32_t new_number);
void print_all(void);

#endif