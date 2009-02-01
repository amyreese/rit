
.PHONY: all
all: nosyncupdate

.PHONY: test
test: nosync0 nosync1 nosyncupdate.c
	gcc -o nosyncupdate -D DEBUG nosyncupdate.c
	./nosyncupdate 0

nosyncupdate: nosync0 nosync1 nosyncupdate.c
	gcc -o nosyncupdate nosyncupdate.c

nosync0: nosync0.c
	gcc -o nosync0 nosync0.c

nosync1: nosync1.c
	gcc -o nosync1 nosync1.c

