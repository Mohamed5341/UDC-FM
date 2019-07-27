#include "i2c.h"


/*
*This function is used to start I2C comunication with slave to start reading process
*--------------------------------------------------
*Input: address is the device address you want to start communication with
*		reg is the register you want to start read from
*Output: None
*/
void start_connection(char address,char reg){
    while(1){
        //write slave address
        I2C1_MSA_R = address<<1;

        //wait for Bus Busy
        while(I2C1_MCS_R&I2C_MCS_BUSBSY){}

        //write data in data register the AC1 register in BMP
        I2C1_MDR_R = reg;

        //start and run transmit process
        I2C1_MCS_R = I2C_MCS_START|I2C_MCS_RUN;

        //wait until transmission ends
        while(I2C1_MCS_R&I2C_MCS_BUSY){}

        //check for errors
        if(I2C1_MCS_R&I2C_MCS_ERROR){
            //there is error happened
            if(I2C1_MCS_R&I2C_MCS_ARBLST){
                //ARBITRATION lost send stop bit
                I2C1_MCS_R = I2C_MCS_STOP;
            }
            continue;
        }

        //write slave address for read
        I2C1_MSA_R = address<<1 | 0x1;

        //send start bit slave address and ack.
        I2C1_MCS_R = I2C_MCS_ACK|I2C_MCS_START|I2C_MCS_RUN;

        break;
    }
}


/*
*This function is used to configure I2C1
*--------------------------------------------------
*Input: None
*Output: None
*/
void init_I2C(void){
    //Enable clock to I2C1
    SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R1;


    //Enable clock to portA
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;


    //Choose alternate function to the pins PA6 & PA7
    GPIO_PORTA_AFSEL_R |= 0x000000C0;


    //Choose the other function of the pins
    GPIO_PORTA_PCTL_R &= ~0xFF000000;
    GPIO_PORTA_PCTL_R |= GPIO_PCTL_PA7_I2C1SDA;
    GPIO_PORTA_PCTL_R |= GPIO_PCTL_PA6_I2C1SCL;


    //enable pins 6 & 7 to be digital
    GPIO_PORTA_DEN_R |= 0x000000C0;


    //Enable pin 7 for open drain
    GPIO_PORTA_ODR_R |= 0x00000080;


    //Configure TivaC as Master
    I2C1_MCR_R |= I2C_MCR_MFE;


    //Set the Clock
    I2C1_MTPR_R |= 0x00000007;

}



/*
*This function is used to get byte from device you started connection with it
*--------------------------------------------------
*Input: stop when is equals STOP_COND this means this is the last variable you want to recieve after that you device will send stop bit
			when it equals NON_STOP_COND this means there is other data so dont send stop bit
*Output: it is the byte you want to recieve
*/
char get_byte(char stop){
    char data;
    //wait until transmission ends
    while(I2C1_MCS_R&I2C_MCS_BUSY){}

    //check for errors
    if(I2C1_MCS_R&I2C_MCS_ERROR){
        //there is error happened
        if(I2C1_MCS_R&I2C_MCS_ARBLST){
            //ARBITRATION lost send stop bit
            I2C1_MCS_R = I2C_MCS_STOP;
        }

    }

    //read data
    data = I2C1_MDR_R;

    if(stop == STOP_COND){
        //send stop bit
        I2C1_MCS_R = I2C_MCS_RUN|I2C_MCS_STOP;
    }else{
        //send stop bit
        I2C1_MCS_R = I2C_MCS_RUN;
    }
    return data;
}



/*
*this function is used to write byte to register with address
*--------------------------------------------------
*Input: address is the address of the slave
		reg is the regester you want to send byte to it
		value is the byte you want to write in the register
*Output: None
*/
void write_byte(char address,char reg,char value){
    while(1){
        //write slave address
        I2C1_MSA_R = address<<1;

        //wait for Bus Busy
        while(I2C1_MCS_R&I2C_MCS_BUSBSY){}

        //write data in data register the AC1 register in BMP
        I2C1_MDR_R = reg;

        //start and run transmit process
        I2C1_MCS_R = I2C_MCS_START|I2C_MCS_RUN;

        //wait until transmission ends
        while(I2C1_MCS_R&I2C_MCS_BUSY){}

        //check for errors
        if(I2C1_MCS_R&I2C_MCS_ERROR){
            //there is error happened
            if(I2C1_MCS_R&I2C_MCS_ARBLST){
                //ARBITRATION lost send stop bit
                I2C1_MCS_R = I2C_MCS_STOP;
            }
            continue;
        }

        //send the data you want to write in register
        I2C1_MDR_R = value;

        //send and stop.
        I2C1_MCS_R = I2C_MCS_RUN|I2C_MCS_STOP;

        //wait until transmission ends
        while(I2C1_MCS_R&I2C_MCS_BUSY){}

        //check for errors
        if(I2C1_MCS_R&I2C_MCS_ERROR){
            //there is error happened
            if(I2C1_MCS_R&I2C_MCS_ARBLST){
                //ARBITRATION lost send stop bit
                I2C1_MCS_R = I2C_MCS_STOP;
            }
            continue;
        }
        break;
    }
}

