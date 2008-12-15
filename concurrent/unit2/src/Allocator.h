#ifndef __ALLOCATOR__
#define __ALLOCATOR__

#include <vector>

#include "Thread.h"
#include "Mutex.h"

class Client;

/**
 * VM Allocator
 * @author John Reese
 * @author Stephen Wright
 */
class Allocator : public Thread
{
public:
	Allocator( int vms, int clients );
	virtual ~Allocator();

	void request( int vms, Client *client );
	void release();
	void status();
	void report( int vms );

	Mutex requestMutex;

protected:
	void assign();
	void crash();
	void free( int vms );

	virtual void setup();
	virtual void execute();

private:
	int max_vms;
	int max_clients;

	// Allocator State
	// 1: Normal operation
	// 2: Assignment
	// 3: Crash recovery
	int state;

	int available;
	int reports;

	int requested;
	int assigned;

	Mutex mutex;

	std::vector<Client*> clients;
	Client *currentClient;
};

#endif //__ALLOCATOR__

