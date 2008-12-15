#include <stdio.h>
#include <vector>

#include "constants.h"
#include "Allocator.h"
#include "Client.h"

using namespace std;

/**
 * VM Allocator
 * @author John Reese
 * @author Stephen Wright
 */

Allocator::Allocator( int vms, int clients ) : Thread() {
	if ( DEBUG > 1 ) {
		printf( "Creating allocator...\n" );
	}

	max_vms = vms;
	max_clients = clients;

	available = max_vms;

	state = 1;
}

Allocator::~Allocator() {
	if ( DEBUG > 1 ) {
		printf( "Destroying allocator...\n" );
	}
}

void Allocator::request( int vms, Client *client ) {
	printf( "Allocator: request[%d]\n", vms );

	MutexLock lock = MutexLock( &mutex );

	requested = vms;
	assigned = 0;

	currentClient = client;

	state = 2;
}

void Allocator::release() {
	printf( "Allocator: release\n" );

	MutexLock lock = MutexLock( &mutex );

	available ++;
}

void Allocator::status() {
	printf( "Allocator: status\n" );

	free( available );
}

void Allocator::free( int vms ) {
	printf( "Allocator: free[%d]\n", vms );
}

void Allocator::report( int vms ) {
	printf( "Allocator: report[%d]\n", vms );

	MutexLock lock = MutexLock( &mutex );

	available -= vms;
	reports ++;

	if ( reports == max_clients ) {
		state = 1;
	}
}

void Allocator::assign() {
	printf( "Allocator: assign\n" );

	MutexLock lock = MutexLock( &mutex );

	available --;
	assigned ++;

	if ( assigned == requested ) {
		state = 1;
	}

	currentClient -> assign();
}

void Allocator::crash() {
	printf( "Allocator: crash\n" );

	vector<Client*>::iterator iter;
	for ( iter = clients.begin(); iter != clients.end(); iter++ ) {
		(*iter) -> crash();
	}

	requestMutex.unlock();

	MutexLock lock = MutexLock( &mutex );

	available = max_vms;
	reports = 0;

	assigned = 0;
	requested = 0;

	state = 3;
}

void Allocator::setup() {
	if ( DEBUG > 1 ) {
		printf( "Setting up allocator...\n" );
	}
}

void Allocator::execute() {
	if ( DEBUG > 1 ) {
		printf( "Executing allocator...\n" );
	}

	for ( int i = 0; i < NCLIENTS; i++ ) {
		Client *c = new Client( this );
		c -> start();
		clients.push_back( c );
	}

	// Infinite execution loop
	while( true ) {
		yield();

		if ( state == 1 ) { // Normal operation
			int choice = randint(1,20);
			if ( choice == 1 ) {
				crash();
			} else if ( choice == 2 ) {
				//status();
			}
		} else if ( state == 2 ) { // Assignment
			int choice = randint(1,20);
			if( choice == 1 ) {
				crash();
			} else {
				assign();
			}
		} else if ( state == 3 ) { // Crash recovery
		}
	}

	vector<Client*>::iterator iter;
	for ( iter = clients.begin(); iter != clients.end(); iter++ ) {
		( *iter ) -> join();
		delete *iter;
	}

}

