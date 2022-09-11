extern char hiasm;

#include "string.h"
#include "dtb.h"
#include <stddef.h>
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


extern void _fw_end();

//called from a.s after setting up the stack pointer in sp
void kmain(size_t hartid, void *dtb) {
	//int hartid = get_hartid();
	if (hartid != 0) {
		while (1) {}
	}

	spec s = get_extensions();
	printf("%s\n",s);

	
	setup_m_handlers();




	fdt_header *hdr = get_header(dtb);
	mem_init(_fw_end,1);

	//print_header(hdr);
	//print_structure(hdr);

	puts("Which demo to run? (0 = priv example, <other> = multithreading example):");

	char ch = getch();
	putchar(10);
	if (ch == '0') {
		delegate_trap(1,8);
		call_in_s_mode(smain);
	} else {
	}
	while (1) {}


	/*
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
