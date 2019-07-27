#include "uart.h"


/*
*This function is used to configure UART0 (115200 Baudrate when system clock 16MHz)
*--------------------------------------------------
*Input: None
*Output: None
*/
void init_uart(void){
    //Provide clock to UART module in this case UART0*/
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;

    //Provide clock to used port in this case port A*/
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

    //Disable UART to avoid error while configuring settings*/
    UART0_CTL_R &= ~UART_CTL_UARTEN;

    //write the integer part to baud rate, the chosen Baud rate is 115200 integer part is 8*/
    UART0_IBRD_R = 8;

    //write the fractional part of Baud rate fraction part is 44*/
    UART0_FBRD_R = 44;

    //Select the system clock to provide clock to UART module*/
    UART0_CC_R |= UART_CC_CS_SYSCLK;

    //modify Line control register to make: data 8bits, no interrupt, no parity, no FIFO and 1 stop bit*/
    UART0_LCRH_R |= UART_LCRH_WLEN_8;

    //Enable transmitter and receiver*/
    UART0_CTL_R |= UART_CTL_RXE | UART_CTL_TXE;

    //Enable UART module*/
    UART0_CTL_R |= UART_CTL_UARTEN;

    //enable digital to pins PA0 PA1 because they are the UART pins*/
    GPIO_PORTA_DEN_R |= 0x00000003;

    //choose another function to the pins*/
    GPIO_PORTA_AFSEL_R |= 0x00000003;

    //select the function to be UART for pins PA0 PA1*/
    GPIO_PORTA_PCTL_R |= GPIO_PCTL_PA0_U0RX | GPIO_PCTL_PA1_U0TX;

    //wait for TX output to stay idle high*/
}


/*
*This function send 1 byte with UART
*--------------------------------------------------
*Input: data is the byte you want to send
*Output: None
*/
void send_char(char data){
    //this loop waits until the data register to be empty*/
    while((UART0_FR_R & UART_FR_TXFF) != 0x00000000)
    {
    }


    //write the data to data register and it will send it the data*/
    UART0_DR_R = data;
}


/*
*This function send decimal using UART
*--------------------------------------------------
*Input: n is the decimal you want to send
*Output: None
*/
void UART_OutUDec(unsigned long n){
// This function uses recursion to convert decimal number
//   of unspecified length as an ASCII string
  if(n >= 10){
    UART_OutUDec(n/10);
    n = n%10;
  }
  send_char(n+'0'); /* n is between 0 and 9 */
}
