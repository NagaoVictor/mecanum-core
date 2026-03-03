#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#include <stdint.h>

#define PCA9685_ADDR 0x40
#define ADC_ADDR 0x48
#define MODE1 0x00
#define PRESCALE 0xFE
#define LED0_ON_L 0x06
#define FL_A 0
#define FL_B 1
#define RL_A 2
#define RL_B 3
#define RR_A 5
#define RR_B 4
#define FR_A 7
#define FR_B 6


extern int fd_i2c; // Usar no arquivo main.c e no motor_driver.c

int init_pca9685();
int set_pwd(int fd, uint8_t ch, uint16_t on);
float battery_core(int fd);
void drive_bridge(int chA, int chB, int speed);
void apply_mecanum(int8_t x, int8_t y, int8_t r);

#endif
