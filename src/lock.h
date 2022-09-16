#pragma once

typedef int lock;
void aquire_lock(lock *lock);
void release_lock(lock *lock);
#define LOCK_INIT 0


void wait_until_set(lock *lock);
void set_lock(lock *lock);
