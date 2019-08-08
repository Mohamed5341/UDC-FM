/*
This library is to calculate airspeed from MPXV7000dp sensor
*/

#ifndef _MPXV7004DP_H_
#define _MPXV7004DP_H_

#include "C:\Keil_v5\EE319Kware\inc\tm4c123gh6pm.h"
#include "math.h"
#include "clock.h"

#define RHO 1.225


/*
*This function is used to initialze ADC0 with pin PE3
*/
void init_adc(void);


/*
*This function is used get sensor output and convert it to speed
*/
float get_speed(void);

#endif


