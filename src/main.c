extern char hiasm;

#include "string.h"
#include "dtb.h"
#include "memory.h"

void kmain(void *a, void *dtb) {
	puts(&hiasm);
	char *str = "booting rvnew";
	puts(str);

	/*
	fdt_header *hdr = get_header(dtb);

	print_header(hdr);
	print_structure(hdr);*/

	mem_init(0x80000000,1);
	char *buf = malloc(50);
	for (;;) {
		getn(buf,50);
		if (strcmp(buf,"x\n") == 0) {
			break;
		} else {
			printf(buf);
		}
	}
	free(buf);
	while (1) {}
}
