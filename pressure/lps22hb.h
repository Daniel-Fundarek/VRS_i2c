/*
 * lps22hb.h
 *
 *  Created on: Nov 15, 2022
 *      Author: DFUNDO
 */

#ifndef LPS22HB_H_
#define LPS22HB_H_

#include "i2c.h"

#define LPS22HB_DEVICE_ADDRESS 0xB9
#define LPS22HB_DEVICE_ADDRESS1 0xBB


#define LPS22HB_WHO_AM_I_ADDRESS 0x0F
#define LPS22HB_WHO_AM_I_VALUE 0xB1

#define LPS22HB_CTRL_REG1 0x10
#define LPS22HB_CTRL2_REG 0x11
#define LPS22HB_CTRL3_REG 0x12

#define LPS22HB_PRESS_OUT_L 0x29
#define LPS22HB_PRESS_OUT_H 0x2A

#define LPS22HB_PRESS_OUT_XL 0x28
#define LPS22HB_TEMP_OUT_L 0x2B
#define LPS22HB_TEMP_OUT_H 0x2C


#define LPS22HB_CTRL1_RESET_REG			0xFF
#define LPS22HB_CTRL1_ENABLE_LOWPASS_FILT (0x1 << 3)
#define LPS22HB_CTRL1_POWERDOWN 		(0x0 << 4)
#define LPS22HB_CTRL1_FREQUENCY_1HZ 	(0x1 << 4)
#define LPS22HB_CTRL1_FREQUENCY_10HZ	(0x2 << 4)
#define LPS22HB_CTRL1_FREQUENCY_25HZ	(0x3 << 4)
#define LPS22HB_CTRL1_FREQUENCY_50HZ	(0x4 << 4)
#define LPS22HB_CTRL1_FREQUENCY_75HZ	(0x5 << 4)


void lps22hb_readArray(uint8_t * data, uint8_t reg, uint8_t length);
void lps22hb_write_byte(uint8_t reg_addr, uint8_t value);
uint8_t lps22hb_read_byte(uint8_t reg_addr);
uint16_t lps22hb_init();
void get_pressure(float* pressure);
#endif /* LPS22HB_H_ */
