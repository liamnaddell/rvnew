#include "dtb.h"
#include "string.h"
#include "byte.h"
#include <stddef.h>


fdt_header *get_header(void *loc) {
	fdt_header *h = (fdt_header *) loc;
	uint32_t mg = betole(h->magic);
	if (mg == 0xd00dfeed) {
		return h;
	} else {
		return NULL;
	}
}


void print_header(fdt_header *h) {
	printf("dtb {\n");
	printf("	magic: %x\n", betole(h->magic));
	printf("	totalsize: %x\n", betole(h->totalsize));
	printf("	off_dt_struct: %x\n", betole(h->off_dt_struct));
	printf("	off_dt_strings: %x\n", betole(h->off_dt_strings));
	printf("	off_mem_rsvmap: %x\n", betole(h->off_mem_rsvmap));
	printf("	version: %x\n", betole(h->version));
	printf("	last_comp_version: %x\n", betole(h->last_comp_version));
	printf("	boot_cpuid_phys: %x\n", betole(h->boot_cpuid_phys));
	printf("	size_dt_strings: %x\n", betole(h->size_dt_strings));
	printf("	size_dt_struct: %x\n", betole(h->size_dt_struct));
	printf("}\n");
}

void print_structure(fdt_header *h) {
	uint32_t *_struct = (uint32_t *) h + betole(h->off_dt_struct);
	uint32_t data = betole(*_struct);
	//skip 6 at beginning lol?
	while (data != 0x9) {
		if (data == 0x4) {
		} else if (data == 0x1 || data == 0x6) {
			printf("NODE {\n");
			char buf[30];
			int i = 0;
			int cont = 1;
			while (cont) {
				_struct++;
				uint32_t chars = betole(*_struct);
				struct str s = utoch(chars);

				
				int j = 0;
				while (j < 4) {
					buf[i] = s.buf[j];
					if (s.buf[j] == 0) {
						cont = 0;
					}
					i++;
					j++;
				}
			}
			_struct++;
			printf("%s\n",buf);
		} else if (data == 0x2) {
			printf("}\n");
		} else if (data == 0x3) {
			_struct++;
			uint32_t len  = betole(*_struct);
			_struct++;
			uint32_t nameoff = betole(*_struct);
			_struct++;
			printf("PROP: len %x, off %x\n",len,nameoff);
		}
		_struct++;
		data = betole(*_struct);
	}
	return;
}
