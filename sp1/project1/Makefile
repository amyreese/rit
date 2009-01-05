allocatedir=/usr/local/pub/wrc/courses/sp1/allocate

cpp=gcc
cflags=-Wall -ggdb -std=c99
output=project1

headers=database.h input.h
sources=database.c input.c project1.c

libflags=-L$(allocatedir) -lallocate
incflags=-I$(allocatedir)

$(output): $(sources) $(headers)
	$(cpp) $(cflags) $(incflags) $(libflags) $(sources) -o $(output)

.PHONY:run
run: $(output)
	./$(output)

.PHONY:clean
clean:
	rm -f $(output)

