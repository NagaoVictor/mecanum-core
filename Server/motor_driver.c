#include <endian.h>
#include <linux/i2c-dev.h> // I2C_SLAVE
#include <fcntl.h> // open()
#include <sys/ioctl.h>
#include <unistd.h>
#include "motor_driver.h"
#include <pthread.h>

static pthread_mutex_t i2c_mutex = PTHREAD_MUTEX_INITIALIZER;

int fd_i2c = -1;

void set_pwm(uint8_t channel, uint16_t value){
	if (fd_i2c < 0) return;
	pthread_mutex_lock(&i2c_mutex);

	ioctl(fd_i2c, I2C_SLAVE, PCA9685_ADDR);
	uint8_t reg = 0x06 + (4 * channel);
	uint8_t buf[5] = {reg, 0x00, 0x00, value & 0xFF, (value >> 8) & 0x0F};
	write(fd_i2c, buf, 5);
	
	pthread_mutex_unlock(&i2c_mutex);
}


void drive_bridge(int chA, int chB, int speed){
	if (speed>=0){
		set_pwm(chA, speed > 4095 ? 4095 : speed);
		set_pwm(chB,0);
	} else {
		set_pwm(chA, 0);
		set_pwm(chB, -speed > 4095 ? 4095 : -speed);
	}
}

int init_pca9685(){
	fd_i2c = open("/dev/i2c-1", O_RDWR);
	if (fd_i2c < 0) return -1;
	
	ioctl(fd_i2c, I2C_SLAVE, PCA9685_ADDR);
	
	uint8_t mode_sleep[] = {MODE1, 0x11};
	write(fd_i2c, mode_sleep, 2);
	
	uint8_t prescale_val[] = {PRESCALE, 0x79};
	write(fd_i2c, prescale_val, 2);
	
	uint8_t mode_wake[] = {MODE1, 0x21};
	write(fd_i2c, mode_wake, 2);

	usleep(5000);
	return fd_i2c;
}


void apply_mecanum(int8_t x, int8_t y, int8_t r){
	ioctl(fd_i2c, I2C_SLAVE, PCA9685_ADDR);
	
	int s = 32;
	
	int fl = (y + x + r) * s;
	int rl = (y - x + r) * s;
	int rr = (y + x - r) * s;
	int fr = (y - x - r) * s;
	
	drive_bridge(0, 1, fl);
	drive_bridge(3, 2, rl);
	drive_bridge(4, 5, rr); 
	drive_bridge(6, 7, fr);

}


