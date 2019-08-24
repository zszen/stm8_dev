
//#include <iostm8s103f3.h>
//#include "stm8s_gpio.h"
#include "stm8s.h"

typedef enum TYPE_Debug{
  TYPE_Debug1,
  TYPE_Debug2,
  TYPE_Debug3,
}TYPE_Debug;

int main()
{
  
 // TYPE_Debug.TYPE_Debug1
  //int abc=123123;
  //printf("%d",TYPE_Debug1);
  GPIO_Init(GPIOC, GPIO_PIN_3,GPIO_MODE_OUT_PP_LOW_FAST);
  return 0;
}
