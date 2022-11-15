//
// Created by DFUNDO on 10/30/2022.
//

#include <stdint-gcc.h>
#include "hts221.h"


static uint8_t hts221_address = HTS221_DEVICE_ADDRESS;


//uint64_t lastMovementTick = 0;

uint8_t hts221_read_byte(uint8_t reg_addr) {
    uint8_t data = 0;
    return *(i2c_master_read(&data, 1, reg_addr, hts221_address, 0));
}

void hts221_write_byte(uint8_t reg_addr, uint8_t value) {
    i2c_master_write(value, reg_addr, hts221_address, 0);
}

void hts221_readArray(uint8_t *data, uint8_t reg, uint8_t length) {
    i2c_master_read(data, length, reg, hts221_address, 0);
}

uint16_t hts221_init() {
    uint16_t status;
    int16_t val = hts221_read_byte(HTS221_WHO_AM_I);
    if (val == HTS221_WHO_AM_I_VALUE) {
        status = 1;
    } else {
        return 0;
    }
    // init registers
    // reg1
    uint8_t control1 = hts221_read_byte(HTS221_CONTROL_REG1);
    control1 &= HTS221_RESET_CONTROL_REG1;
    control1 |= HTS221_SET_PD_CONTROL_REG1;
    control1 |= HTS221_SET_BDU_CONTROL_REG1;
    control1 |= HTS221_1HZ_CONTROL_REG1;
    hts221_write_byte(HTS221_CONTROL_REG1, control1);

    /*uint8_t control2 = hts221_read_byte(HTS221_CONTROL_REG2);
    control2 &= HTS221_RESET_CONTROL_REG2;
    control2 |= HTS221_SET_BOOT_CONTROL_REG2;
    hts221_write_byte(HTS221_CONTROL_REG2, control2);*/

   // uint8_t control3 = hts221_read_byte(HTS221_CONTROL_REG3);


    return status;

}

void hts221_get_humidity(float* humidity){
	uint8_t H0_rH_x2 = hts221_read_byte(HTS221_HUMIDITY_CAL_H0_RH);
	uint8_t H1_rH_x2 = hts221_read_byte(HTS221_HUMIDITY_CAL_H1_RH);

	int16_t H0_cal = hts221_read_byte(HTS221_HUMIDITY_CAL_H0_LSB);
	H0_cal = (hts221_read_byte(HTS221_HUMIDITY_CAL_H0_MSB)<<8);

	int16_t H1_cal = hts221_read_byte(HTS221_HUMIDITY_CAL_H1_LSB);
	H1_cal = (hts221_read_byte(HTS221_HUMIDITY_CAL_H1_MSB)<<8);

	int16_t H = hts221_read_byte(HTS221_HUMIDITY_OUT_LSB);
	H = (hts221_read_byte(HTS221_HUMIDITY_OUT_MSB)<<8);

	float k = (H1_rH_x2 - H0_rH_x2) / (float)(H1_cal - H0_cal);
	float q = H1_rH_x2 - k * H1_cal;

	*humidity = (k*H + q)/2.0f;



}



void hts221_get_temp(float* temp) {
    //uint8_t temp[2];
    //temp[0] = 0;
    //temp[1] = 0;
    //hts221_readArray(temp, HTS221_TEMP_OUT_H, 2);
    //hts221_readArray(temp1,HTS221_TEMP_OUT_L,8);


    int16_t T_OUT = (hts221_read_byte(HTS221_TEMP_OUT_H)<<8);
    T_OUT= (hts221_read_byte(HTS221_TEMP_OUT_L));

    int16_t T0_OUT= (hts221_read_byte(0x3D)<<8);
    T0_OUT = T0_OUT | hts221_read_byte(0x3C);

    int16_t T1_OUT= (hts221_read_byte(0x3F)<<8);
    T1_OUT = T1_OUT | hts221_read_byte(0x3E);

    uint16_t T0_deg = hts221_read_byte(0x32);
    uint16_t T1_deg = hts221_read_byte(0x33);

	uint8_t T1T0msb = hts221_read_byte(0x35);

	int16_t T1msb = ((T1T0msb  >> 2 ) & 0x3) << 8;
	int16_t T0msb = ((T1T0msb & 0x3 ) << 8);

	T0_deg = (T0_deg | T0msb);
	T1_deg = (T1_deg | T1msb);


    float k =  (float)(T1_deg - T0_deg)/(T1_OUT - T0_OUT);
	float q = (float)(T1_deg - T1_OUT* k);

	float temperature = (k * T_OUT + q)/8.0f;
	/*
    msbT0T1 &= 0xF;
    uint16_t msbT0 = msbT0T1 & 0x3;
    uint16_t calibrationT0 = msbT0 << 8;
    calibrationT0 |= T0_deg;
    uint16_t msbT1 = (msbT0T1 >> 2) & 0x3;
    uint16_t calibrationT1 = msbT1 << 8;
    calibrationT1 |= T1_deg;
    uint16_t calibration = (calibrationT0 + calibrationT1) / 2 / 8;*/
    *temp = temperature;


}

