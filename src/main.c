extern char hiasm;

#include "string.h"
#include "dtb.h"

void kmain(void *a, void *dtb) {
	char buf[50];
	puts(&hiasm);
	char *str = "booting rvnew";
	puts(str);

	fdt_header *hdr = get_header(dtb);

	print_header(hdr);
	print_structure(hdr);
	
	for (;;) {
		getn(buf,50);
	}
}
