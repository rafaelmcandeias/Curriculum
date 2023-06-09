#ifndef LOCKS
#define LOCKS

#include <pthread.h>

void init_trinco(pthread_rwlock_t trinco);
void destroy(pthread_rwlock_t trinco);
void lock(pthread_rwlock_t trinco, int flag);
void unlock(pthread_rwlock_t trinco);

#endif