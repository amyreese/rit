#include <stdio.h>
#include <pthread.h>

#include "Mutex.h"

/**
 * Generic POSIX Mutex class.
 * @author John Reese
 */

Mutex::Mutex() {
	pthread_mutex_init( &mutex, NULL );
}

Mutex::~Mutex() {}

void Mutex::lock() {
	pthread_mutex_lock( &mutex );
}

void Mutex::unlock() {
	pthread_mutex_unlock( &mutex );
}

/**
 * Generic scope-based Mutex lock.
 * @author John Reese
 */

MutexLock::MutexLock( Mutex *m ) {
	mutex = m;
	mutex->lock();
}

MutexLock::~MutexLock() {
	mutex->unlock();
}

