//
// Created by DFUNDO on 10/30/2022.
//

#include <stdint-gcc.h>
#include "hts221.h"


static uint8_t address = HTS221_DEVICE_ADDRESS;

//uint64_t lastMovementTick = 0;

uint8_t hts221_read_byte(uint8_t reg_addr) {
    uint8_t data = 0;
    return *(i2c_master_read(&data, 1, reg_addr, address, 0));
}

void hts221_write_byte(uint8_t reg_addr, uint8_t value) {
    i2c_master_write(value, reg_addr, address, 0);
}

void hts221_readArray(uint8_t *data, uint8_t reg, uint8_t length) {
    i2c_master_read(data, length, reg, address, 0);
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
    control1 &= HTS221_7HZ_CONTROL_REG1;
    hts221_write_byte(HTS221_CONTROL_REG1, control1);

    /*uint8_t control2 = hts221_read_byte(HTS221_CONTROL_REG2);
    control2 &= HTS221_RESET_CONTROL_REG2;
    control2 |= HTS221_SET_BOOT_CONTROL_REG2;
    hts221_write_byte(HTS221_CONTROL_REG2, control2);*/

   // uint8_t control3 = hts221_read_byte(HTS221_CONTROL_REG3);


    return status;

}

int16_t hts221_get_temp(float* x, float* y, float* z) {
    uint8_t temp[2];
    temp[0] = 0;
    temp[1] = 1;
    hts221_readArray(temp, HTS221_TEMP_OUT_H, 2);
    //hts221_readArray(temp1,HTS221_TEMP_OUT_L,8);
    uint16_t msbT0T1 = 0;
    msbT0T1 = hts221_read_byte(0x35);
    uint16_t T0_deg = hts221_read_byte(0x32);
    uint16_t T1_deg = hts221_read_byte(0x33);
    msbT0T1 &= 0xF;
    uint16_t msbT0 = msbT0T1 & 0x3;
    uint16_t calibrationT0 = msbT0 << 8;
    calibrationT0 |= T0_deg;
    uint16_t msbT1 = (msbT0T1 >> 2) & 0x3;
    uint16_t calibrationT1 = msbT1 << 8;
    calibrationT1 |= T1_deg;
    uint16_t calibration = (calibrationT0 + calibrationT1) / 2 / 8;
    *x = msbT0T1;
    *y = temp[0];
    *z = temp[1];

}

