cpp=gcc
cflags=-Wall -ggdb -std=c99
output=project1
sources=project1.c

allocatedir=/usr/local/pub/wrc/course/sp1/allocate
libflags=#-L$(allocatedir) -lallocate

$(output): $(sources)
	$(cpp) $(cflags) $(libflags) $(sources) -o $(output)

.PHONY:run
run: $(output)
	./$(output)

.PHONY:clean
clean:
	rm -f $(output)

