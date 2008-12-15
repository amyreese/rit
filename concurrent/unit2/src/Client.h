#ifndef __CLIENT__
#define __CLIENT__

#include "Thread.h"
#include "Mutex.h"

class Allocator;

/**
 * VM consumer
 * @author John Reese
 * @author Stephen Wright
 */
class Client : public Thread
{
public:
	Client( Allocator *a );
	virtual ~Client();

	void assign();
	void crash();

protected:
	void work();
	void request( int vms );
	void use();
	void release();
	void report( int vms );

	virtual void setup();
	virtual void execute();

private:
	// Client State
	// 1: Normal operation
	// 2: Requesting VM units
	// 3: Crash recovery
	int state;

	bool crashed;

	Allocator *allocator;

	int requested;
	int allocated;

	Mutex mutex;
};

#endif //__CLIENT__

