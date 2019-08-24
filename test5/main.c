/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "STM8S103F.h"

main()
{
	PA_DDR = 0xff;
	PA_ODR = 0xff;
	
	while (1);
}