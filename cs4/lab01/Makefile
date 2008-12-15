#
# Created by gmakemake (Sparc Feb 24 2004) on Mon Mar  8 19:29:32 2004
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


CPP_FILES =	NumberPair.cpp NumberToGuess.cpp mastermind.cpp
C_FILES =	
H_FILES =	NumberPair.h NumberToGuess.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES)
.precious:	$(SOURCEFILES)
OBJFILES =	NumberPair.o NumberToGuess.o

#
# Main targets
#

all:	mastermind 

mastermind:	mastermind.o $(OBJFILES)
	$(CCC) $(CCFLAGS) -o mastermind mastermind.o $(OBJFILES) $(LIBFLAGS)

#
# Dependencies
#

NumberPair.o:	NumberPair.h
NumberToGuess.o:	NumberPair.h NumberToGuess.h
mastermind.o:	NumberPair.h NumberToGuess.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -r $(OBJFILES) mastermind.o core 2> /dev/null

realclean:	clean
	/bin/rm -rf mastermind 
