#include "bmp180.h"


/*
*This function is used to read calibration variables (AC1,AC2,AC3, ...)
*--------------------------------------------------
*Input: None
*Output: None
*/
void calibrations(void){
	
	oss = OSS_VAL;
	
	start_connection(BMP_ADDRESS,AC1_REGESTER_MSB);
    AC1 = (get_byte(NON_STOP_COND) << 8) | get_byte(STOP_COND);
    start_connection(BMP_ADDRESS,AC2_REGESTER_MSB);
    AC2 = (get_byte(NON_STOP_COND) << 8) | get_byte(STOP_COND);
    start_connection(BMP_ADDRESS,AC3_REGESTER_MSB);
    AC3 = (get_byte(NON_STOP_COND) << 8) | get_byte(STOP_COND);
    start_connection(BMP_ADDRESS,AC4_REGESTER_MSB);
    AC4 = (get_byte(NON_STOP_COND) << 8) | get_byte(STOP_COND);
    start_connection(BMP_ADDRESS,AC5_REGESTER_MSB);
    AC5 = (get_byte(NON_STOP_COND) << 8) | get_byte(STOP_COND);
    start_connection(BMP_ADDRESS,AC6_REGESTER_MSB);
    AC6 = (get_byte(NON_STOP_COND) << 8) | get_byte(STOP_COND);
    start_connection(BMP_ADDRESS,B1_REGESTER_MSB);
    B1 = (get_byte(NON_STOP_COND) << 8) | get_byte(STOP_COND);
    start_connection(BMP_ADDRESS,B2_REGESTER_MSB);
    B2 = (get_byte(NON_STOP_COND) << 8) | get_byte(STOP_COND);
    start_connection(BMP_ADDRESS,MB_REGESTER_MSB);
    MB = (get_byte(NON_STOP_COND) << 8) | get_byte(STOP_COND);
    start_connection(BMP_ADDRESS,MC_REGESTER_MSB);
    MC = (get_byte(NON_STOP_COND) << 8) | get_byte(STOP_COND);
    start_connection(BMP_ADDRESS,MD_REGESTER_MSB);
    MD = (get_byte(NON_STOP_COND) << 8) | get_byte(STOP_COND);
	
}

/*
*This function is used to get temperature
*--------------------------------------------------
*Input: None
*Output: temperature in c
*/
float get_temp(void){
	write_byte(BMP_ADDRESS,BMP_CONTROL_MEASUREMENTS_R, CTRL_MEAS_TEMPERATURE);
	delayMs(5);
	start_connection(BMP_ADDRESS,OUT_MSB);
	UT = (get_byte(NON_STOP_COND) << 8) | get_byte(STOP_COND);
	
	X1 = (UT-AC6)*AC5 /32768;
	X2 = MC * 2048/(X1+MD);
	B5 = X1+X2;
	T = (B5+8)/16;
	
	return T/10.0;
}

/*
*This function is used to get Pressure
*--------------------------------------------------
*Input: None
*Output: pressure in pa
*/
long get_press(void){
	write_byte(BMP_ADDRESS,BMP_CONTROL_MEASUREMENTS_R, CTRL_MEAS_PRESSURE_OSS);
	delayMs(OSS_DELAY);
	start_connection(BMP_ADDRESS,OUT_MSB);
	up_msb = get_byte(NON_STOP_COND);
	up_lsb = get_byte(NON_STOP_COND);
	up_xlsb = get_byte(STOP_COND);
	UP = ((up_msb << 16) | (up_lsb << 8) | up_xlsb)>>(8-oss);
	
	
	B6 = B5-4000;

	X1 = (B2 *(B6*B6/4096))/2048;
	X2 = AC2 * B6 / 2048;
	X3 = X1 + X2;
	B3 = (((AC1* 4 + X3)<<oss)+2)/4;
	X1 = AC3 * B6 / 8192;
	X2 = (B1 * (B6 * B6 / 4096))/65536;
	X3 = ((X1+X2)+2)/4;
	B4 = AC4 * (X3 + 32768)/32768;
	B7 = (UP - B3)*(50000>>oss);

	if(B7<0x80000000){
	  P = (B7*2)/B4;
	}else{
	  P = (B7/B4)*2;
	}

	X1 = (P/256)*(P/256);
	X1 = (X1 * 3038)/65536;
	X2 = (-7357*P)/65536;
	P = P + (X1+X2+3791)/16;
	
	return P;
}


/*
*This function is used to dalay for certain time
*--------------------------------------------------
*Input: None
*Output: None
*/
void delayMs(int n){
    int i,j;

    for(i=0;i<n;i++){
        for(j=0;j<3180;j++){

        }
    }
}


/*
*This function is used to calculate altitude
*--------------------------------------------------
*Input: None
*Output: altitude in meter
*/
float get_altitude(void){
	altitude = 44330*(1-pow(P*1.0/P0,1/5.255));
	return altitude;
}

