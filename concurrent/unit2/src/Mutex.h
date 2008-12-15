#ifndef __POSIX_MUTEX__
#define __POSIX_MUTEX__

#include <pthread.h>

/**
 * Generic POSIX Mutex class.
 * @author John Reese
 */
class Mutex
{
public:
	/**
	 * Create a new Mutex.
	 */
	Mutex();

	/**
	 * Destroy a Mutex.
	 */
	~Mutex();

	/**
	 * Lock the Mutex.
	 */
	void lock();

	/**
	 * Unlock the Mutex.
	 */
	void unlock();

private:
	// The POSIX mutex
	pthread_mutex_t mutex;
};

/**
 * Generic scope-based Mutex lock.
 * Automatically locks given mutex, then unlocks when destroyed.
 * Useful for synchronizing an entire block of scope against a Mutex.
 * @author John Reese
 */
class MutexLock
{
public:
	/**
	 * Create a scope-based MutexLock and lock the given Mutex.
	 * @param The Mutex to be locked and unlocked
	 */
	MutexLock( Mutex *m );

	/**
	 * Destroy the MutexLock after unlocking the Mutex.
	 */
	~MutexLock();
private:
	// The locked Mutex
	Mutex *mutex;
};

#endif // __POSIX_MUTEX__

