extern char hiasm;

#include "string.h"
#include "dtb.h"
#include "memory.h"
#include "smain.h"

typedef struct spec {
	char extensions[26];
} spec;

//what extensions are supported
spec get_extensions() {
	spec s;
	char *letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	uint64_t reg; 
	asm volatile("csrrs %0, misa, x0" : "=r"(reg) : :);
	int i;
	int j = 0;
	int mask = 1;
	for (i = 0; i < 26; i++) {
		if (reg & mask) {
			s.extensions[j] = letters[i];
			j++;
		}
		mask = mask << 1;
	}
	s.extensions[i] = 0;
	return s;
}

//the identifier for the current hart (cpu thread)
uint64_t get_hartid() {
	uint64_t mhartid;
	asm volatile("csrrs %0, mhartid, x0" : "=r"(mhartid) : :);
	return mhartid;
}

uint64_t get_mtvec() {
	uint64_t mtvec;
	asm volatile("csrrs %0, mtvec, x0" : "=r"(mtvec) : :);
	return mtvec;
}

//what function do we call on a trap
void set_mtvec(void *addr) {
	uint64_t mtvec = (((uint64_t) addr) << 0) & ~(0b11) ;
	asm volatile("csrrw %0, mtvec, %0" : : "r"(mtvec):);
	return;
}

typedef struct exception_cause {
	//exception code
	unsigned int code;
	//interrupt or error/exception
	char interrupt;
} exception_cause;

//why an exception was caused
exception_cause get_mcause() {
	uint64_t mcause;
	asm volatile("csrrs %0, mcause, x0" : "=r"(mcause) : :);
	exception_cause ec;
	ec.interrupt = mcause >> 63;
	ec.code = mcause & ~(1LL << 63);
	return ec;
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

//switches the processor from M-mode to S-mode, which is has less privlige
void call_in_s_mode(void *fn) {
	disable_pmp();
	//change spp field to 1 to switch to s-mode instead of u-mode
	uint64_t eight = 1 << 8;
	asm volatile("csrrs %0, mstatus,%0" : : "r"(eight):);
	asm volatile("csrrw %0, sepc, %0" : : "r"(fn):);
	asm volatile("sret" : : :);
}

void delegate_trap(int e_or_i, int number) {
	number = 1 << number;
	if (e_or_i) {
		asm volatile("csrrs %0, medeleg, %0" : : "r"(number):);
	} else {
		asm volatile("csrrs %0, mideleg, %0" : : "r"(number):);
	}
}

//for all 32 megabytes of memory, make it RWX in all processor modes, pmp= physical memory protection
void disable_pmp() {
	//32MB of memory starting at 0x80000000
	uint64_t top = 0x82000000;
	asm volatile("csrrw %0, pmpaddr0, %0" : : "r"(top):);
	//                   L  AARWX
	uint64_t pmp0cfg = 0b10001111;
	asm volatile ("csrrw %0, pmpcfg0, %0" : : "r"(pmp0cfg));
}

//defined in a.s, calls m_mode_c_handler
extern void m_mode_handler();

//called from a.s after setting up the stack pointer in sp
void kmain(void *a, void *dtb) {
	int hartid = get_hartid();
	if (hartid != 0) {
		while (1) {}
	}
	puts(&hiasm);


	spec s = get_extensions();
	printf("%s\n",s);

	
	set_mtvec(m_mode_handler);




	fdt_header *hdr = get_header(dtb);

	print_header(hdr);
	print_structure(hdr);


	delegate_trap(1,8);
	call_in_s_mode(smain);

	/*mem_init(0x80000000,1);
	char *buf = malloc(50);
	for (;;) {
		getn(buf,50);
		if (strcmp(buf,"x\n") == 0) {
			break;
		} else {
			printf(buf);
		}
	}
	free(buf);*/
	while (1) {}
}
