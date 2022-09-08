#include "string.h" 
#include <stdint-gcc.h>

void s_mode_c_handler() {
	puts("exception recieved in S mode");
	while (1) {}
}


void u_hi() {
	puts("hi from u-mode");
	asm volatile("scall" : : :);
}


void call_in_u_mode(void *fn) {
	//change spp field to 1 to switch to s-mode instead of u-mode
	uint64_t eight = 1 << 8;
	asm volatile("csrrc %0, sstatus,%0" : : "r"(eight):);
	asm volatile("csrrw %0, sepc, %0" : : "r"(fn):);
	asm volatile("sret" : : :);
}

void set_stvec(void *addr) {
	uint64_t stvec = (((uint64_t) addr) << 0) & ~(0b11) ;
	asm volatile("csrrw %0, stvec, %0" : : "r"(stvec):);
}

extern void s_mode_handler();

void smain() {
	puts("Hi from S mode");

	set_stvec(s_mode_handler);

	call_in_u_mode(u_hi);


	//go back to m-mode and end
	asm volatile("ecall" : : :);
}
