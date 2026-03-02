#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <stdint.h>

typedef struct __attribute__((packed)) {
	int8_t x;
	int8_t y;
	int8_t r;
	uint8_t flags;
} RobotCommand;

#endif
