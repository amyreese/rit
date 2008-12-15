#ifndef __POSIX_THREAD__
#define __POSIX_THREAD__

#include <pthread.h>

/**
 * Generic POSIX thread class for managing the lifetime of a thread.
 * @author John Reese
 */
class Thread
{
public:
	/**
	 * Create a new Thread object.
	 */
	Thread();

	/**
	 * Destroy a thread object.
	 */
	virtual ~Thread();

	/**
	 * Spawn a new thread from this object.
	 * @return error code
	 */
	int start();

	/**
	 * Join a thread to wait for it's completion.
	 * @return error code
	 */
	int join();

protected:
	/**
	 * Called by thread management to prepare the thread for execution.
	 * Meant to be overridden by inheriting classes.
	 */
	virtual void setup();

	/**
	 * Called by thread management to begin thread execution, main loop, etc.
	 * Meant to be overridden by inheriting classes.
	 */
	virtual void execute();

	/**
	 * Yield thread execution if possible.
	 */
	void yield();

	// Thread ID
	int id;

private:
	/**
	 * Entry point for new threads.
	 * @param pointer to the thread object
	 */
	static void * entry(void*);

	// Thread counter
	static int counter;

	/**
	 * Called by the thread entry point to get the thread going.
	 */
	void run();

	/**
	 * Called by thread management to exit the thread.
	 */
	void end();

	// Track the thread's state
	bool started, stopped;

	// Pthread information
	pthread_t thread;
};

#endif //__POSIX_THREAD__

