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
	 uint16_t status;
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
	 control1 = control1 | LPS22HB_CTRL1_ENABLE_LOWPASS_FILT | LPS22HB_CTRL1_FREQUENCY_1HZ;

	 hts221_write_byte(LPS22HB_CTRL_REG1, control1);
}
void lps22hb_get_pressure(float* pressure){
	uint32_t p = hts221_read_byte(LPS22HB_TEMP_OUT_XL);
	p = (hts221_read_byte(LPS22HB_TEMP_OUT_L) << 8);
	p = (hts221_read_byte(LPS22HB_TEMP_OUT_H) << 16);
	*pressure = p;
}

