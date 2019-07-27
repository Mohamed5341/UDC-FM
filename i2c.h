/*
*This library is to use configure and send data using I2C
*/

#ifndef _I2C_H_
#define _I2C_H_

#include "C:\Keil_v5\EE319Kware\inc\tm4c123gh6pm.h"

#define STOP_COND 1
#define NON_STOP_COND 0


/*
*This function is used to configure I2C1
*/
void init_I2C(void);


/*
*This function is used to start I2C comunication with slave to start reading process
*/
void start_connection(char address,char reg);


/*
*This function is used to get byte from device you started connection with it
*/
char get_byte(char stop);


/*
*this function is used to write byte to register with address
*/
void write_byte(char address,char reg,char value);

#endif
