#ifndef LOCKS
#define LOCKS

#include <pthread.h>

void mutex_unlock();
void mutex_lock();
void init_trinco();
void destroy();
void lock(int flag, int debug);
void unlock(int debug);

#endif