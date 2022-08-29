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

typedef struct nodes {
	//current node, can be a child node
	uint32_t *offset;
	//what depth in are we?
	int level;
} nodes;

typedef struct node {
	//where the node is in memory
	uint32_t *offset;
} node;

nodes get_nodes(fdt_header *hdr);
node next_node(fdt_header *hdr, nodes *ns);


//an iterator through the properties
typedef struct properties {
	//offset is null if there are no properties or no properties left
	uint32_t *offset;
} properties;

typedef struct property {
	uint32_t *key;
	uint32_t *value;
} property;

/* dtb reading API */

//returns null when not found
//fix api, this does NOT need malloc, return pointers and lengths! better string API!
node get_path(fdt_header *hdr, char *s);
properties get_props(fdt_header *hdr, node n);
property next_prop(fdt_header *hdr, properties *ps);
char *node_name(node n);
