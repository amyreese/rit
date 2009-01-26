#
# Created by gmakemake (Sparc Aug  2 2007) on Sun Jan 25 11:49:47 2009
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c

########## Flags from header.mak

SUPPORTDIR =	/usr/local/pub/wrc/courses/sp1/project2
CC =		gcc
AS =		gas

#
# Standard set of options (these will be used by 'try')
#
CFLAGS =	-nodefaultlibs
LIBFLAGS =	-L$(SUPPORTDIR) -lsupport
#
# For testing purposes, if you want to use the C library, 
# comment out the previous two lines and uncomment the following
# two lines (which will use an alternate version of the
# support library that will play nicely with the C library).
#
# CFLAGS =	
# LIBFLAGS =	-L$(SUPPORTDIR) -lsupport1

CLIBFLAGS =	$(LIBFLAGS)

.s.o:
		gas --gstabs $< -o $@

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	
S_FILES =	qas.s
H_FILES =	
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	

#
# Main targets
#

all:	qas

qas:	qas.o $(OBJFILES)
	$(CC) $(CFLAGS) -o qas qas.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#


#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) qas.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf qas 
