#include "mpxv7002dp.h"


/*
*This function is used to initialze ADC0 with pin PE3
*--------------------------------------------------
*Input: None
*Output: None
*/
void init_adc(void){
	init_clock_PLL();

    //Enable clock to port E
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;


    //Enable clock to ADC0 module
    SYSCTL_RCGCADC_R |= SYSCTL_RCGCADC_R0;

    //Choose alternate function to PE3
    GPIO_PORTE_AFSEL_R |= 0x00000008;

    //Disable digital function to pin PE3
    GPIO_PORTE_DEN_R &= ~(0x00000008);

    //Enable analog mode to pin PE3
    GPIO_PORTE_AMSEL_R |= 0x00000008;

    //Disable sample sequencer
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN3;

    //Choose processor trigger
    ADC0_EMUX_R &= ~ADC_EMUX_EM3_ALWAYS;

    //Choose channel 0
    ADC0_SSMUX3_R = 0x00000000;

    //Single endded option, one conversion sample and raw interrupt
    ADC0_SSCTL3_R |= ADC_SSCTL3_END0 | ADC_SSCTL3_IE0;

    //Enable sample sequencer
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN3;
}


/*
*This function is used get sensor output and convert it to speed
*--------------------------------------------------
*Input: None
*Output: airspeed in m/s
*/
float get_speed(void){
	int output;
    float volt,dp,speed;
	
	//Begin measuring
	ADC0_PSSI_R |= ADC_PSSI_SS3;

	//Wait until conversion is done
	while(ADC0_RIS_R&ADC_RIS_INR3 == 0){}

	//Read data
	output = ADC0_SSFIFO3_R;

	//Clear flag bit
	ADC0_ISC_R &= ~ADC_ISC_IN3;

	//convert output to volt (*5/3.3 because of voltage divider)
	volt = (output * 3.3 / 4096.0);

	//get pressure difference
	dp = 5 * (volt/5 - 0.5);

	//calculate airspeed
	speed = sqrt(2*dp/RHO);
	
	
	return speed;
}
