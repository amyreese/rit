allocatedir=/usr/local/pub/wrc/courses/sp1/allocate

cpp=gcc
cflags=-Wall -ggdb -std=c99
output=project1

headers=input.h project1.h database.h
sources=input.c project1.c database.c database_course.c database_student.c database_enrollment.c

libflags=-L$(allocatedir) -lallocate
incflags=-I$(allocatedir)

$(output): $(sources) $(headers)
	$(cpp) $(cflags) $(incflags) $(sources) -o $(output) $(libflags)

.PHONY:run
run: $(output)
	./$(output) -v

.PHONY:test
test: $(output)
	cd tests; ./RUN

.PHONY:clean
clean:
	rm -f $(output) core MAX_MEMORY_USED tests/core tests/MAX_MEMORY_USED tests/err.* tests/out.*

