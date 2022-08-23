#include "dtb.h"
#include "string.h"


fdt_header get_header(void *loc) {
	fdt_header *floc = (fdt_header *) loc;
	return *floc;
}

void print_header(fdt_header h) {
	printf("dtb {\n");
	printf("	magic: %x\n", h.magic);
	printf("}\n");
}
