#include "exceptions.h"
#include <stdint-gcc.h>

//why an exception was caused
exception_cause get_mcause() {
	uint64_t mcause;
	asm volatile("csrrs %0, mcause, x0" : "=r"(mcause) : :);
	exception_cause ec;
	ec.interrupt = mcause >> 63;
	ec.code = mcause & ~(1LL << 63);
	return ec;
}
