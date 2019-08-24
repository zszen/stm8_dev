
#ifndef Zszen_Std_ZConst
#define Zszen_Std_ZConst\

//boolean #include "stm8s_type.h"
//typedef enum {false = 0, true = !false} bool;

//uint
#define uint unsigned int 

//BIT(num)  BIT(2) 0b0100
#ifndef BIT 
#define BIT(x) (1 << (x))
#endif

#endif