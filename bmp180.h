/*
*this library is to calculate pressure ,temperature and altitude from BMP180
*/


#ifndef _BMP180_H_
#define _BMP180_H_

#include "C:\Keil_v5\EE319Kware\inc\tm4c123gh6pm.h"
#include "math.h"
#include "i2c.h"

#define P0 100470
#define BMP_ADDRESS 0x77
#define BMP_CONTROL_MEASUREMENTS_R 0xF4
#define STOP_COND 1
#define NON_STOP_COND 0
#define OSS0

#define CTRL_MEAS_TEMPERATURE 0x2E


#define OUT_MSB 0xF6
#define OUT_LSB 0xF7
#define OUT_XLSB 0xF8


#define AC1_REGESTER_MSB 0xAA
#define AC1_REGISTER_LSB 0xAB
#define AC2_REGESTER_MSB 0xAC
#define AC2_REGISTER_LSB 0xAD
#define AC3_REGESTER_MSB 0xAE
#define AC3_REGISTER_LSB 0xAF
#define AC4_REGESTER_MSB 0xB0
#define AC4_REGISTER_LSB 0xB1
#define AC5_REGESTER_MSB 0xB2
#define AC5_REGISTER_LSB 0xB3
#define AC6_REGESTER_MSB 0xB4
#define AC6_REGISTER_LSB 0xB5
#define B1_REGESTER_MSB 0xB6
#define B1_REGISTER_LSB 0xB7
#define B2_REGESTER_MSB 0xB8
#define B2_REGISTER_LSB 0xB9
#define MB_REGESTER_MSB 0xBA
#define MB_REGISTER_LSB 0xBB
#define MC_REGESTER_MSB 0xBC
#define MC_REGISTER_LSB 0xBD
#define MD_REGESTER_MSB 0xBE
#define MD_REGISTER_LSB 0xBF
#define ID_R 0xD0


#ifdef OSS0
    #define CTRL_MEAS_PRESSURE_OSS 0x34
    #define OSS_DELAY 5
	#define OSS_VAL 0
#endif

#ifdef OSS1
    #define CTRL_MEAS_PRESSURE_OSS 0x74
    #define OSS_DELAY 8
	#define OSS_VAL 1
#endif

#ifdef OSS2
    #define CTRL_MEAS_PRESSURE_OSS 0xB4
    #define OSS_DELAY 14
	#define OSS_VAL 2
#endif

#ifdef OSS3
    #define CTRL_MEAS_PRESSURE_OSS 0xF4
    #define OSS_DELAY 26
	#define OSS_VAL 3
#endif

short AC1,AC2,AC3,B1,B2,MB,MC,MD;
unsigned short AC4,AC5,AC6;
long UT,UP,X1,X2,X3,B3,B5,B6,T,P;
unsigned long B4,B7;
char up_msb,up_lsb,up_xlsb;
float altitude;
unsigned char oss;


/*
*This function is used to dalay for certain time
*/
void delayMs(int n);

/*
*This function is used to read calibration variables (AC1,AC2,AC3, ...)
*/
void calibrations(void);

/*
*This function is used to get temperature
*/
float get_temp(void);

/*
*This function is used to get Pressure
*/
long get_press(void);

/*
*This function is used to calculate altitude
*/
float get_altitude(void);


#endif


