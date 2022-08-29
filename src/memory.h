#pragma once

void mem_init(void *base_addr, unsigned int pageno);

void *malloc(long unsigned int bytes);
void free(void *addr);
