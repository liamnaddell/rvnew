#pragma once

void aquire_lock(int *lock);
void release_lock(int *lock);
typedef int lock;
#define LOCK_INIT 0
