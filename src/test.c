extern char hiasm;

#include "string.h"
#include "dtb.h"
#include "memory.h"

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

void m_mode_c_handler() {
	while (1){}
}

void kmain(void *a, void *dtb) {

	int l;
	aquire_lock(&l);

	puts("TEST SUITE");
	testfn tests[3] = {
		strcmp_basic,
		strcmp_basic2,
		strcmp_basic3
	};
	for (int i = 0; i < 1; i++) {
		int res = tests[i]();
		if (res == 1) {
			printf("TEST %d PASSED\n", i);
		} else {
			printf("TEST %d FAILED\n", i);
		}
	}
	release_lock(&l);
	while (1) {}
}
