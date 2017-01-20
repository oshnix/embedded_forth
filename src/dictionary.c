/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */

#include "main.h"
#include "dictionary.h"

/* USER CODE END Includes */


/* USER CODE BEGIN 0 */

void add(void){
  --stack_data;
  *stack_data += *(stack_data + 1);
}

void put(int32_t new_number){
  *(++stack_data) = new_number;
}

#define STRUCT {0, "+", 0, add}

void sub(void){
  --stack_data;
  *stack_data -= *(stack_data + 1);;
}


/*
#undef PREVIOUS
#define PREVIOUS STRUCT
#undef STRUCT
#define STRUCT &{PREVIOUS, "-", 0, sub}
*/








/* USER CODE END 0 */