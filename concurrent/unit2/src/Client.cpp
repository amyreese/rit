#include <stdio.h>

#include "constants.h"
#include "Allocator.h"
#include "Client.h"

/**
 * VM consumer
 * @author John Reese
 * @author Stephen Wright
 */

Client::Client( Allocator *a ) : Thread() {
	if ( DEBUG > 1 ) {
		printf( "Creating client...\n" );
	}

	state = 1;
	allocated = 0;
	requested = 0;

	allocator = a;
}

Client::~Client() {
	if ( DEBUG > 1 ) {
		printf( "Destroying client...\n" );
	}
}

void Client::assign() {
	printf( "Client %d: assign\n", id );

	MutexLock lock = MutexLock( &mutex );

	allocated += 1;

	if ( allocated == requested ) {
		state = 1;
		allocator->requestMutex.unlock();
	}
}

void Client::crash() {

	MutexLock lock = MutexLock( &mutex );

	printf( "Client %d: crash\n", id );

	crashed = true;
}

void Client::work() {

	printf( "Client %d: work\n", id );
}

void Client::request( int vms ) {

	mutex.lock();

	printf( "Client %d: request[%d]\n", id, vms );

	requested = vms;
	state = 2;

	mutex.unlock();

	allocator->requestMutex.lock();
	if ( crashed ) {
		allocator->requestMutex.unlock();
		return;
	}

	allocator->request( vms, this );
}

void Client::use() {

	printf( "Client %d: use\n", id );
}

void Client::release() {

	printf( "Client %d: release\n", id );

	MutexLock lock = MutexLock( &mutex );

	allocator->release();
	allocated -= 1;
}

void Client::report( int vms ) {

	printf( "Client %d: report[%d]\n", id, vms );

	MutexLock lock = MutexLock( &mutex );

	allocator->report( vms );
}

void Client::setup() {
	if ( DEBUG > 1 ) {
		printf( "Setting up client...\n" );
	}
}

void Client::execute() {
	if ( DEBUG > 1 ) {
		printf( "Executing client...\n" );
	}

	int choice;

	// Infinite execution loop
	while( true ) {
		//printf( "Client %d has %d/%d units in state %d.\n", id, allocated, requested, state );
		yield();

		if ( state == 1 ) { // Normal operation
			if ( crashed ) {
				mutex.lock();
				crashed = false;
				mutex.unlock();

				report( allocated );
				continue;
			}

			if ( allocated ) {
				choice = randint(1,2);
				switch( choice ) {
					case 1:
						use();
						break;
					case 2:
						release();
						break;
				}
			} else  {
				choice = randint(1,2);
				switch( choice ) {
					case 1:
						work();
						break;
					case 2:
						request(randint(1,REQUEST_MAX));
						break;
				}
			}
		} else if ( state == 2 ) { // Requesting units
			if ( crashed ) {
				mutex.lock();
				crashed = false;
				mutex.unlock();

				report( allocated );

				if ( allocated ) {
					mutex.lock();
					state = 3;
					mutex.unlock();
				} else {
					request( requested );
				}
			}
		} else if ( state == 3 ) { // Crash recovery
			if ( crashed ) {
				mutex.lock();
				crashed = false;
				mutex.unlock();

				report( allocated );
			}

			if ( allocated ) {
				release();
			} else {
				request(requested);
			}
		}
	}
}

