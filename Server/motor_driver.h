#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#include <stdint.h>

#define PCA9685_ADDR 0x40
#define ADC_ADDR 0x48
#define MODE1 0x00
#define PRESCALE 0xFE
#define LED0_ON_L 0x06

extern int fd_i2c; // Usar no arquivo main.c e no motor_driver.c

int init_pca9685();
int set_pwd(int fd, uint8_t ch, uint16_t on, uint16_t off);
float battery_core(int fd);

#endif
