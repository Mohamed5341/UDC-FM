#include "clock.h"



/*
*This function is used to configure clock to be 16MHz using PLL
*--------------------------------------------------
*Input: None
*Output: None
*/
void init_clock_PLL(){
    //Enable RCC2 Register
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;


    //Use OSC Not PLL
    SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;


    //Use 16MHz for PLL as its input is Main OSC (16MHz)
    SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;
    SYSCTL_RCC_R |= SYSCTL_RCC_XTAL_16MHZ;


    //Use Main OSC in both RCC & RCC2
    SYSCTL_RCC_R &= ~SYSCTL_RCC_OSCSRC_MAIN;
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;
    SYSCTL_RCC2_R |= SYSCTL_RCC2_OSCSRC2_MO;


    //Run PLL
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;


    //Use DIV400 so the output from PLL will be 400MHz
    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;


    //divide the output (400MHz) by 25 so the out is 16MHz and this by writing 24 in SYSDIV
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~(SYSCTL_RCC2_SYSDIV2_M|SYSCTL_RCC2_SYSDIV2LSB)) + (24<<22);


    //Wait until PLL stabilise
    while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){}


    //Turn the Output to PLL
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}



/*
*This function is used to configure clock to be 16MHz main oscilator
*--------------------------------------------------
*Input: None
*Output: None
*/
void init_clock_MOSC(void){
    //Disable RCC2 Register
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_USERCC2;


    //get the clock from OSC
    SYSCTL_RCC_R |= SYSCTL_RCC_BYPASS;


    //Use Main OSC in both
    SYSCTL_RCC_R &= ~SYSCTL_RCC2_OSCSRC2_M;


    //Don't use SYSDIV so the output will be the clock without changing
    SYSCTL_RCC_R &= ~SYSCTL_RCC_USESYSDIV;
}

