cpp=gcc
cflags=-Wall
output=mash
sources=mash.c

$(output):
	$(cpp) $(cflags) $(sources) -o $(output)

.PHONY:run
run: $(output)
	./$(output)

.PHONY:clean
clean:
	rm -f $(output)
