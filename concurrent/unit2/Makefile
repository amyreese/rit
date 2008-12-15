.DEFAULT_GOAL	= all

DEBUG	= 2

CPP	= g++
CFLAGS	= -pipe -Wall -O2 -D DEBUG=$(DEBUG)

LINK	= g++

OBJECTS	:= $(patsubst src/%.cpp,tmp/%.o,$(wildcard src/*.cpp))

LIBS	= -L/usr/lib -lpthread
INC	= -I. -I$(SOURCES_DIR) -I/usr/include

TARGET	= Allocator

### RULES


.PHONY : all clean fresh

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(LINK) -o $(TARGET) $(LIBS) $(OBJECTS)

$(OBJECTS) : tmp/%.o : src/%.cpp
	$(CPP) -c $(CFLAGS) $(INC) -o $@ $<

clean :
	-rm -f $(OBJECTS) $(TARGET)

fresh : clean all
	./$(TARGET)
