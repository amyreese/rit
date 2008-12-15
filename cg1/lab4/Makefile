
TARGET	= lab4

HEADERS		= 
OBJECTS		= lab4.o

# System Settings

CC	= g++
CFLAGS	= -W $(patsubst %.h, -include %.h, $(HEADERS))

INCLUDE	= -I. -I/usr/include
LIBS	= -L/usr/lib -lglut 

# Rules

.PHONY : all
all : $(TARGET)

.PHONY : fresh
fresh : clean bleach all

.PHONY : test
test : $(TARGET)
	./$<

$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $(LIBS) $+

$(OBJECTS) : %.o : %.cpp
	$(CC) -o $@ -c $(CFLAGS) $(INCLUDE) $<

.PHONY : clean
clean :
	rm -f $(OBJECTS) 

.PHONY : bleach
bleach : clean
	rm -f $(TARGET)

