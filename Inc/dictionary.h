
#ifndef STM32_DICTIONARY
#define STM32_DICTIONARY

typedef struct word{
  struct word *previous;
  char *name;
  uint8_t flag;
  void(*xt)();
}word;

extern word last_word;
void add(void);
void put(int32_t new_number);

#endif