
#ifndef STM32_DICTIONARY
#define STM32_DICTIONARY

/* USER STRUCT DEFINITION BEGIN*/

/*special struct to itterate through words*/
struct word_description{
  struct word_description *previous;
  char name[7];
  char flag;
  void(*xt[])();
};

/*struct for embedded words only*/
struct colon_word{
  struct colon_word *previous;
  char name[7];
  char flag;
  void(*xt[1])();
};
/* struct for words putxt, : and ;*/
struct word_put_xt{
  struct colon_word *previous;
  char name[7];
  char flag;
  void(*doc[1])();
  void(**xt[3])();
};

struct word_begin_compilation{
  struct word_put_xt *previous;
  char name[7];
  char flag;
  void(*doc[1])();
  void(**xt[12])();
};

struct word_end_compilation{
  struct word_begin_compilation *previous;
  char name[7];
  char flag;
  void(*doc[1])();
  void(**xt[6])();
};

/*USER STRUCT DEFINITION END*/

#define LOOP_LENGTH 70

/* Public variables definitions ----------------------------------------------*/
/* USER CODE PV BEGIN */
extern struct colon_word *last_word;
extern void(**interpretator_loop[LOOP_LENGTH])();
extern void(***current_xt)(void);
extern void(**current_word)(void);
extern void (**next_xt_space)(void);
/* USER CODE PV END */

/* Public functions prototypes -----------------------------------------------*/
/* USER CODE PF BEGIN */
/* USER CODE PF END */
#endif