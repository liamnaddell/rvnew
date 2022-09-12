extern char hiasm;

#include "string.h"
#include "dtb.h"
#include "memory.h"
#include "traps.h"
#include "lock.h"
#include <stddef.h>

typedef int (*testfn)();

int strcmp_basic() {
	char *s1 = "Hello World!";
	char *s2 = "Hello World!";
	int res = strcmp(s1,s2);
	return res == 0;
}
int strcmp_basic2() {
	char *s1 = "Hello orld!";
	char *s2 = "Hello World!";
	int res = strcmp(s1,s2);
	return res != 0;
}
int strcmp_basic3() {
	char *s1 = "Hello";
	char *s2 = "Hello World!";
	int res = strcmp(s1,s2);
	return res != 0;
}
int malloc_basic() {
	char *a = malloc(10);
	char *b = malloc(10);
	if (a == b) {
		return 0;
	}
	return 1;
}
int malloc_basic2() {
	char *a = malloc(10);
	char *b = malloc(10);
	free(a);
	char *c = malloc(10);
	if (c == b) {
		return 0;
	} else if (c == a) {
		return 1;
	}
	return 0;
}

int malloc_stress(char ch) {
	for (int i = 1; i < 1000; i++) {
		char *b = malloc(i);
		memset(b,ch,i);
		for (int j = 0; j < i; j++) {
			if (b[j] != ch) {
				printf("%d: memory coherency violated",ch);
				return;
			}
		}
		free(b);
	}
}

lock l = LOCK_INIT;

extern void _fw_end();

void kmain(size_t hartid, void *dtb) {
	setup_m_handlers();
	if (hartid == 0) {
		mem_init(_fw_end,10);
	}

	//multicore test
	malloc_stress((char) hartid);

	//disable multicore support for now
	aquire_lock(&l);

	puts("TEST SUITE");
	int i = 0;
	int res;
	res = malloc_basic();
	i++;
	if (res == 0) {
		goto fail;
	}

	res = malloc_basic2();
	i++;
	if (res == 0) {
		goto fail;
	}
	goto success;
fail:
	printf("TEST %d FAILED\n", i);
	goto end;
success:
	printf("TEST SUITE SUCCESSFUL\n");
end:
	//don't run test suite again
	//release_lock(&l);
	while (1) {}
}
