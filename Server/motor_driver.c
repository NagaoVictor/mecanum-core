#include <endian.h>
#include <linux/i2c-dev.h> // I2C_SLAVE
#include <fcntl.h> // open()
#include <sys/ioctl.h>
#include <unistd.h>
#include "motor_driver.h"

int fd_i2c = -1;

int init_pca9685(){
	fd_i2c = open("/dev/i2c-1", O_RDWR);
	if (fd_i2c < 0) return -1;
	if (ioctl(fd_i2c, I2C_SLAVE, PCA9685_ADDR) < 0){
		close(fd_i2c);
		return -2;
	}
	uint8_t buf[2] = {MODE1, 0x01};
	write(fd_i2c, buf, 2);
	return fd_i2c;
}





float battery_core(int fd){
	uint16_t raw;
	uint8_t reg = 0x00;

	if (ioctl(fd, I2C_SLAVE, ADC_ADDR)<0) return -1.0f;
	
	write(fd, &reg, 1);
	if (read(fd, &raw, 2) != 2) return -1.0f;
	
	raw = be16toh(raw);

	ioctl(fd, I2C_SLAVE, PCA9685_ADDR);

	return (raw* 0.0001875f) * 3.0f;
}
