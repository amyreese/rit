
CC	= gcc
CFLAGS	= -W

INCLUDE	= -I. -I/usr/include
LIBS	= -L/usr/lib -lglut 

TARGET	= lab1

OBJECTS	= $(patsubst %.c, %.o, $(wildcard *.c) )
# Rules

.PHONY : all
all : $(TARGET)

.PHONY : fresh
fresh : clean bleach all

run : all
	./$(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $(LIBS) $(OBJECTS)

$(OBJECTS) : %.o : %.c
	$(CC) -o $@ -c $(CFLAGS) $(INCLUDE) $<

.PHONY : clean
clean :
	rm -f $(OBJECTS)

.PHONY : bleach
bleach : 
	rm -f $(TARGET)
