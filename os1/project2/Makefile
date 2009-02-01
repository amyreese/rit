
.PHONY: all
all: syncupdate nosyncupdate

.PHONY: testnosync
testnosync: nosync0 nosync1 nosyncupdate.c
	gcc -o nosyncupdate -D DEBUG nosyncupdate.c
	./nosyncupdate 0

.PHONY: testsync
testsync: sync0 sync1 syncupdate.c
	gcc -o syncupdate -D DEBUG syncupdate.c
	./syncupdate 0

nosyncupdate: nosync0 nosync1 nosyncupdate.c
	gcc -o nosyncupdate nosyncupdate.c

nosync0: nosync0.c
	gcc -o nosync0 nosync0.c

nosync1: nosync1.c
	gcc -o nosync1 nosync1.c

syncupdate: sync0 sync1 syncupdate.c
	gcc -o syncupdate syncupdate.c

sync0: sync0.c
	gcc -o sync0 sync0.c

sync1: sync1.c
	gcc -o sync1 sync1.c

