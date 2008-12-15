#
# Created by gmakemake (Sparc Feb 24 2004) on Sat Apr  3 13:48:31 2004
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


CPP_FILES =	Calculator.cpp main.cpp
C_FILES =	
H_FILES =	Calculator.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES)
.precious:	$(SOURCEFILES)
OBJFILES =	Calculator.o

#
# Main targets
#

all:	main 

main:	main.o $(OBJFILES)
	$(CCC) $(CCFLAGS) -o main main.o $(OBJFILES) $(LIBFLAGS)

#
# Dependencies
#

Calculator.o:	Calculator.h
main.o:	Calculator.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -r $(OBJFILES) main.o core 2> /dev/null

realclean:	clean
	/bin/rm -rf main 
