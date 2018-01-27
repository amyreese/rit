
LINE_TARGET	= lineTest
FILL_TARGET	= fillTest
CLIP_TARGET	= clipTest

HEADERS		= drawStuff.h
OBJECTS		= setPixel.o drawStuff.o
LINE_OBJECTS	= lineTest.o
FILL_OBJECTS	= fillTest.o
CLIP_OBJECTS	= clipTest.o

# System Settings

CC	= g++
CFLAGS	= -W $(patsubst %.h, -include %.h, $(HEADERS))

INCLUDE	= -I. -I/usr/include
LIBS	= -L/usr/lib -lglut -lGL -lGLU

# Rules

.PHONY : all
all : $(LINE_TARGET) $(FILL_TARGET) $(CLIP_TARGET)

.PHONY : fresh
fresh : clean bleach all

.PHONY : test
test : line fill clip

line : $(LINE_TARGET)
	./$<

fill : $(FILL_TARGET)
	./$<

clip : $(CLIP_TARGET)
	./$<

$(LINE_TARGET) : $(OBJECTS) $(LINE_OBJECTS)
	$(CC) $+ -o $@ $(LIBS)

$(FILL_TARGET) : $(OBJECTS) $(FILL_OBJECTS)
	$(CC) $+ -o $@ $(LIBS)

$(CLIP_TARGET) : $(OBJECTS) $(CLIP_OBJECTS)
	$(CC) $+ -o $@ $(LIBS)

$(OBJECTS) : %.o : %.cpp
	$(CC) -o $@ -c $(CFLAGS) $(INCLUDE) $<

$(LINE_OBJECTS) : %.o : %.c
	$(CC) -o $@ -c $(CFLAGS) $(INCLUDE) $<

$(FILL_OBJECTS) : %.o : %.c
	$(CC) -o $@ -c $(CFLAGS) $(INCLUDE) $<

$(CLIP_OBJECTS) : %.o : %.c
	$(CC) -o $@ -c $(CFLAGS) $(INCLUDE) $<

.PHONY : clean
clean :
	rm -f $(OBJECTS) $(LINE_OBJECTS) $(FILL_OBJECTS) $(CLIP_OBJECTS)

.PHONY : bleach
bleach : clean
	rm -f $(LINE_TARGET) $(FILL_TARGET) $(CLIP_TARGET)

