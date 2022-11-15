/*
 * lps22hb.c
 *
 *  Created on: Nov 15, 2022
 *      Author: DFUNDO
 */
#include "lps22hb.h"
#include <stdint-gcc.h>

uint8_t lps22hb_address = LPS22HB_DEVICE_ADDRESS;
uint8_t lps22hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, lps22hb_address, 0));
}


void lps22hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, lps22hb_address, 0);
}


void lps22hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, lps22hb_address, 0);
}

uint16_t lps22hb_init(){
	 uint16_t status = 0;
	    int16_t val = lps22hb_read_byte(LPS22HB_WHO_AM_I_ADDRESS);
	    if (val == LPS22HB_WHO_AM_I_VALUE) {
	        status = 1;
	    } else {
	    	lps22hb_address = LPS22HB_DEVICE_ADDRESS1;
	    	val = lps22hb_read_byte(LPS22HB_WHO_AM_I_ADDRESS);
	    	 if (val == LPS22HB_WHO_AM_I_VALUE) {
	    		        status = 1;
	    	 }
	    	 else{
	    		return 0;
	    	 }
	    }

	 uint8_t control1 = lps22hb_read_byte(LPS22HB_CTRL_REG1);
	 control1 = LPS22HB_CTRL1_RESET_REG;
	 control1 = control1 |0x18;//| LPS22HB_CTRL1_ENABLE_LOWPASS_FILT | LPS22HB_CTRL1_FREQUENCY_1HZ;

	 lps22hb_write_byte(LPS22HB_CTRL_REG1, control1);
	 return status;
}
void lps22hb_get_pressure(float* pressure){
	int32_t p = 0;
	uint8_t xl = lps22hb_read_byte(LPS22HB_PRESS_OUT_XL);
	uint8_t l = lps22hb_read_byte(LPS22HB_PRESS_OUT_L);
	int8_t h = lps22hb_read_byte(LPS22HB_PRESS_OUT_H);
	p = xl | (l <<8) | (h <<16);
	//p = p | (lps22hb_read_byte(LPS22HB_PRESS_OUT_L) << 8);
	//p = p | (lps22hb_read_byte(LPS22HB_PRESS_OUT_H) << 16);
	*pressure = p/4096.0f;
}


void lps22hb_get_height(float* height ){
	int p=0;
	int T = 0;
	int p0 = 1024;
	//*height = (((p0/p)^(1/5.257)-1)*(T + 273.15))/0.0065;
}

