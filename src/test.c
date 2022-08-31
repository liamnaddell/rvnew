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

const int n = 1;

void kmain(void *a, void *dtb) {
	puts("TEST SUITE");
	testfn tests[1] = {
		strcmp_basic,
	};
	for (int i = 0; i < n; i++) {
		int res = tests[i]();
		if (res == 1) {
			printf("TEST %d PASSED\n", i);
		} else {
			printf("TEST %d FAILED\n", i);
		}
	}
	while (1) {}
}
