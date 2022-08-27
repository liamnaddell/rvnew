#include <stdint-gcc.h>
#include "byte.h"

uint32_t betole(uint32_t data) {
	uint32_t res = 0;
	res += (data & 0xff) << 24;
	res += (data & 0xff00) << 8;
	res += (data & 0xff0000) >> 8;
	res += (data & 0xff000000) >> 24;
	return res;
}

struct str utoch(uint32_t data) {
	struct str s;
	s.buf[3] = data & 0xff;
	s.buf[2] = (data & 0xff00) >> 8;
	s.buf[1] = (data & 0xff0000) >> 16;
	s.buf[0] = (data & 0xff000000) >> 24;
	s.buf[4] = '\0';
	return s;
}
