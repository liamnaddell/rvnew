#include "string.h"
#include "memory.h"

typedef struct matrix {
	int r;
	int w;
	double *data;
} matrix;

struct matmul {
	matrix A;
	matrix B;
	matrix C;
	int num_cpus;
};

struct matmul instance;

void do_matmul() {
	while (1) {}
}

matrix new_matrix(int r, int w) {
	matrix m;
	m.r = r;
	m.w = w;
	m.data = malloc(r*w*sizeof(double));
	return m;
}
void setup_matmul() {
	instance.A = new_matrix(2,2);
	instance.B = new_matrix(2,2);
	instance.C = new_matrix(2,2);
	instance.num_cpus = 2;
	puts("setting up");
}
