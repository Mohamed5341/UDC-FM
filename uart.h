/*
*This library is used to configure UART and send data
*/

#ifndef _UART_H_
#define _UART_H_

#include "C:\Keil_v5\EE319Kware\inc\tm4c123gh6pm.h"

/*
*This function is used to configure UART0 (115200 Baudrate when system clock 16MHz)
*/
void init_uart(void);

/*
*This function send 1 byte with UART
*/
void send_char(char data);

/*
*This function send decimal using UART
*/
void UART_OutUDec(unsigned long n);

#endif
