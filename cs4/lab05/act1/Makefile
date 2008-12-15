#
# Created by gmakemake (Sparc Feb 24 2004) on Mon Apr  5 19:09:56 2004
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


CPP_FILES =	Student.cpp StudentCounter.cpp lab5.cpp
C_FILES =	
H_FILES =	Student.h StudentCounter.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES)
.precious:	$(SOURCEFILES)
OBJFILES =	Student.o StudentCounter.o

#
# Main targets
#

all:	lab5 

lab5:	lab5.o $(OBJFILES)
	$(CCC) $(CCFLAGS) -o lab5 lab5.o $(OBJFILES) $(LIBFLAGS)

#
# Dependencies
#

Student.o:	Student.h
StudentCounter.o:	Student.h StudentCounter.h
lab5.o:	Student.h StudentCounter.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -r $(OBJFILES) lab5.o core 2> /dev/null

realclean:	clean
	/bin/rm -rf lab5 
