/*
*This library is used to configure clock speed
*/

#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "C:\Keil_v5\EE319Kware\inc\tm4c123gh6pm.h"

/*
*This function is used to configure clock to be 16MHz using PLL
*/
void init_clock_PLL(void);


/*
*This function is used to configure clock to be 16MHz main oscilator
*/
void init_clock_MOSC(void);

#endif
