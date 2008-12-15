#
# Created by gmakemake (Sparc Feb 24 2004) on Sat May  1 15:57:54 2004
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


CPP_FILES =	Scanner.cpp SymbolTable.cpp tli.cpp
C_FILES =	
H_FILES =	Scanner.h SymbolTable.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES)
.precious:	$(SOURCEFILES)
OBJFILES =	Scanner.o SymbolTable.o

#
# Main targets
#

all:	tli 

tli:	tli.o $(OBJFILES)
	$(CCC) $(CCFLAGS) -o tli tli.o $(OBJFILES) $(LIBFLAGS)

#
# Dependencies
#

Scanner.o:	Scanner.h SymbolTable.h
SymbolTable.o:	
tli.o:	Scanner.h SymbolTable.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -r $(OBJFILES) tli.o core 2> /dev/null

realclean:	clean
	/bin/rm -rf tli 
