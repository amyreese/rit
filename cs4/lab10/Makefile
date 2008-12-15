#
# Created by gmakemake (Sparc Mar 30 2004) on Sat May 15 16:56:09 2004
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	$(SUFFIXES:.cc=.C .cpp)

.C:
		$(LINK.cc) -o $@ $< $(LDLIBS)
.cpp:
		$(LINK.cc) -o $@ $< $(LDLIBS)
.C.o:
		$(COMPILE.cc) $(OUTPUT_OPTION) $<
.cpp.o:
		$(COMPILE.cc) $(OUTPUT_OPTION) $<
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CCC =		g++

########## Default flags (redefine these with a header.mak file if desired)
CCFLAGS =	-ggdb
CFLAGS =	-ggdb
LIBFLAGS =	-lm
########## End of default flags


CPP_FILES =	ArrayedStack.cpp LinkedStack.cpp Stack.cpp StackTestDriver.cpp StackTester.cpp Watcher.cpp
C_FILES =	
H_FILES =	ArrayedStack.h LinkedStack.h Stack.h StackTester.h Watcher.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES)
.precious:	$(SOURCEFILES)
OBJFILES =	ArrayedStack.o LinkedStack.o Stack.o StackTester.o Watcher.o

#
# Main targets
#

all:	StackTestDriver 

StackTestDriver:	StackTestDriver.o $(OBJFILES)
	$(CCC) $(CCFLAGS) -o StackTestDriver StackTestDriver.o $(OBJFILES) $(LIBFLAGS)

#
# Dependencies
#

ArrayedStack.o:	ArrayedStack.h Stack.h Watcher.h
LinkedStack.o:	LinkedStack.h Stack.h Watcher.h
Stack.o:	Stack.h Watcher.h
StackTestDriver.o:	LinkedStack.h Stack.h StackTester.h Watcher.h
StackTester.o:	Stack.h StackTester.h Watcher.h
Watcher.o:	Watcher.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -r $(OBJFILES) StackTestDriver.o core 2> /dev/null

realclean:	clean
	/bin/rm -rf StackTestDriver 
