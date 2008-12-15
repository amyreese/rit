#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "Thread.h"

/**
 * Generic POSIX thread class for managing the lifetime of a thread.
 * @author John Reese
 */

// Intialize thread ID counter
int Thread::counter = 1;

Thread::Thread() {
	id = Thread::counter++;
	started = false;
	stopped = true;

	if ( DEBUG > 2 ) {
		printf( "Thread %d ready.\n", id );
	}
}

Thread::~Thread() {
	if ( DEBUG > 2 ) {
		printf( "Destroying thread %d...\n", id );
	}

	if ( !stopped ) {
		fprintf( stderr, "Thread object destroyed before stopped; joining...\n" );
		join();
	}
}

int Thread::start() {
	if ( DEBUG > 2 ) {
		printf( "Thread %d starting...\n", id );
	}

	if ( !started ) { // only start once
		started = true;
		stopped = false;
		return pthread_create( &thread, NULL, Thread::entry, this );
	} else {
		return -1; // already started
	}
}

int Thread::join() {
	if ( DEBUG > 2 ) {
		printf( "Joining thread %d...\n", id );
	}

	if ( started ) {
		int code = pthread_join( thread, NULL );
		stopped = true;
		return code;
	} else {
		return -1;
	}
}

//// PROTECTED MEMBERS ////

void Thread::yield() {
	if ( DEBUG > 3 ) {
		printf( "Thread %d yielding...\n", id );
	}

	time_t start = time( NULL );
	time_t now;

	do {
		sched_yield();
		now = time( NULL );
	} while ( now <= start );

	if ( DEBUG > 3 ) {
		printf( "Thread %d returning...\n", id );
	}
}

//// PRIVATE MEMBERS ////

void Thread::run() {
	if ( DEBUG > 2 ) {
		printf( "Thread %d running...\n", id );
	}

	setup();
	execute();
	end();
}

void Thread::end() {
	if ( DEBUG > 2 ) {
		printf( "Thread %d ending...\n", id );
	}

	stopped = true;
	pthread_exit( NULL );
}

void * Thread::entry(void * pthis) {
	Thread * t = (Thread*)pthis;
	t->run();

	return NULL;
}

//// VIRTUAL MEMBERS ////

void Thread::setup() {}
void Thread::execute() {}

