extern char hiasm;

#include "string.h"
#include "dtb.h"
#include "memory.h"

extern uint64_t csrread(uint64_t csrno);


typedef struct spec {
	char extensions[26];
} spec;

spec get_extensions() {
	spec s;
	char *letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	uint64_t reg = csrread(0x301);
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

void set_mtvec(void *addr) {
	//why 4, do research maybe, riscv priviledged says 4 byte boundry, but 2 workd
	uint64_t mtvec = (((uint64_t) addr) << 0) & ~(0b11) ;
	asm volatile("csrrw %0, mtvec, %0" : : "r"(mtvec):);
	return;
}

void interrupt_handler() {
	puts("exception handled");
	while (1) {}
}


void kmain(void *a, void *dtb) {

	int hartid = get_hartid();
	if (hartid != 0) {
		while (1) {}
	}

	puts(&hiasm);
	char *str = "booting rvnew";
	puts(str);

	spec s = get_extensions();
	printf("%s\n",s);

	
	set_mtvec(interrupt_handler);
	printf("mtvec: %x",get_mtvec() >> 2);

	asm volatile("lw t0, 0(x0)" : : :);

	/*
	fdt_header *hdr = get_header(dtb);

	print_header(hdr);
	print_structure(hdr);*/

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
