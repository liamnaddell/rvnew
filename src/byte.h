#pragma once 

#include <stdint-gcc.h>

uint32_t betole(uint32_t data);

struct str {
	char buf[5];
};
//null terminated
struct str utoch(uint32_t data);
