#pragma once
//sauce:https://devicetree-specification.readthedocs.io/en/latest/chapter5-flattened-format.html

#include <stdint-gcc.h>

typedef struct fdt_header {
    uint32_t magic;
    uint32_t totalsize;
    uint32_t off_dt_struct;
    uint32_t off_dt_strings;
    uint32_t off_mem_rsvmap;
    uint32_t version;
    uint32_t last_comp_version;
    uint32_t boot_cpuid_phys;
    uint32_t size_dt_strings;
    uint32_t size_dt_struct;
} fdt_header;

fdt_header *get_header(void *loc);
void print_header(fdt_header *hdr);
uint32_t print_structure(fdt_header *hdr);
