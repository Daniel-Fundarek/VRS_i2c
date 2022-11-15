//
// Created by DFUNDO on 10/30/2022.
//

#ifndef I2C_COMM_HTS221_H
#define I2C_COMM_HTS221_H

#include "i2c.h"


#define HTS221_DEVICE_ADDRESS 0xBF


#define HTS221_WHO_AM_I 0x0F
#define HTS221_WHO_AM_I_VALUE 0xBC
#define HTS221_AVERAGE_CONF 0x10

#define HTS221_AVERAGE_CONF_TEMPERATURE 0x13

//*((volatile uint8_t *)((uint8_t)
#define HTS221_AVERAGE_CONF_HUMIDITY 0x10


#define HTS221_CONTROL_REG1  0x20

#define HTS221_RESET_CONTROL_REG1 0x0 // use =& to reset register
#define HTS221_SET_PD_CONTROL_REG1 0x1<<7 // use |= to set PD

#define HTS221_SET_BDU_CONTROL_REG1 0x1<<2 //use |= to set BDU

#define HTS221_1HZ_CONTROL_REG1 0x1  //use |= to set 1HZ temperature and humidity frequency
#define HTS221_7HZ_CONTROL_REG1 0x2 //use |= to set 7HZ temperature and humidity frequency
#define HTS221_12.5HZ_CONTROL_REG1 0x3	  //use |= to set 12.5HZ temperature and humidity frequency


#define HTS221_CONTROL_REG2 0x21

#define HTS221_RESET_CONTROL_REG2 0x0 // use =& to reset register

#define HTS221_SET_BOOT_CONTROL_REG2 0x1<<7 //use |= to set boot

#define HTS221_SET_HEATER_CONTROL_REG2 0x2 //use |= to set heater

#define HTS221_SET_ONESHOT_CONTROL_REG2 0x1 //use |= to set oneshot

//#define HTS221_RESET-control_REG2

#define HTS221_CONTROL_REG3 0x22


#define HTS221_STATUS_REG 0x27
#define HTS221_HUMIDITY_OUT_L 0x28
#define HTS221_HUMIDITY_OUT_H 0x29
#define HTS221_TEMP_OUT_L 0x2A
#define HTS221_TEMP_OUT_H 0x2B

uint8_t hts221_read_byte(uint8_t reg_addr);

void hts221_write_byte(uint8_t reg_addr, uint8_t value);

void hts221_readArray(uint8_t *data, uint8_t reg, uint8_t length);

uint16_t hts221_init();

int16_t hts221_get_temp();


#endif //I2C_COMM_HTS221_H
