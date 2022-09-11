#include "lock.h"
void aquire_lock(lock *l) {
	volatile int one = 1;
	while (one != 0) {
		asm volatile("amoswap.w.aq %0,%1,0(%2)" : "=r"(one) : "r"(one), "r"(l) : );
	}
}

void release_lock(lock *l) {

	asm volatile("amoswap.w.rl x0,x0,0(a0)" : : "r"(l) : );

}
