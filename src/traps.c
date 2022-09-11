#include "exceptions.h"
#include <stdint-gcc.h>
#include "string.h"

//defined in a.s, calls m_mode_c_handler
extern void m_mode_handler();

//what function do we call on a trap
void set_mtvec(void *addr) {
	uint64_t mtvec = (((uint64_t) addr) << 0) & ~(0b11) ;
	asm volatile("csrrw %0, mtvec, %0" : : "r"(mtvec):);
	return;
}

void *read_mepc() {
	void *mepc;
	asm volatile("csrrs %0, mepc, x0" : "=r"(mepc) : :);
	return mepc;
}

//shouldn't be a C function, should be an asm function
void m_mode_c_handler() {
	puts("exception handled: ");
	exception_cause ec = get_mcause();
	void *pc;
	pc = read_mepc();
	printf("(pc: %p), interrupt: %d, code: %d\n",pc,ec.interrupt, ec.code);

	while (1) {}
}
void setup_m_handlers() {
	set_mtvec(m_mode_handler);
}
