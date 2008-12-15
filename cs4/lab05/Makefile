#
# Created by gmakemake (Sparc Feb 24 2004) on Mon Apr  5 20:04:59 2004
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


CPP_FILES =	Job.cpp Person.cpp test1.cpp test2.cpp
C_FILES =	
H_FILES =	Job.h Person.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES)
.precious:	$(SOURCEFILES)
OBJFILES =	Job.o Person.o

#
# Main targets
#

all:	test1 test2 

test1:	test1.o $(OBJFILES)
	$(CCC) $(CCFLAGS) -o test1 test1.o $(OBJFILES) $(LIBFLAGS)

test2:	test2.o $(OBJFILES)
	$(CCC) $(CCFLAGS) -o test2 test2.o $(OBJFILES) $(LIBFLAGS)

#
# Dependencies
#

Job.o:	Job.h Person.h
Person.o:	Job.h Person.h
test1.o:	Person.h
test2.o:	Person.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -r $(OBJFILES) test1.o test2.o core 2> /dev/null

realclean:	clean
	/bin/rm -rf test1 test2 
