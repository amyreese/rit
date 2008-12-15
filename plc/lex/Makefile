#
# Definitions
#

CC =		gcc
CCC =		g++

CCFLAGS =	-ggdb
CFLAGS =	-ggdb
LIBFLAGS =	-lm

H_FILES =	calc2.h comp.h lisp.h
LEX_FILES =	calc1.lex calc2.lex comp.lex lisp.lex
Y_FILES =	calc2.y comp.y lisp.y
OUTPUT_FILES =	calc2.output comp.output lisp.output

SOURCEFILES =	$(H_FILES) $(LEX_FILES) $(Y_FILES)
.precious:	$(SOURCEFILES)

INTERMEDIATE =	calc1.yy.c calc2.tab.c calc2.yy.c comp.tab.c comp.yy.c lisp.tab.c lisp.yy.c $(OUTPUT_FILES)

EXECS = calc1 calc2 comp lisp	

#
# Main targets
#

all:	 calc1 calc2 lisp comp

calc1:	calc1.yy.c
	$(CC) $(CFLAGS) -o calc1 calc1.yy.c

calc1.yy.c:	calc1.lex
	flex -ocalc1.yy.c calc1.lex

calc2:	calc2.tab.c calc2.yy.c
	$(CC) $(CFLAGS) -o calc2 calc2.tab.c

calc2.yy.c:	calc2.lex
	flex -ocalc2.yy.c calc2.lex

calc2.tab.c:	calc2.y calc2.h
	bison -v calc2.y

lisp:	lisp.tab.c lisp.yy.c
	$(CC) $(CFLAGS) -o lisp lisp.tab.c

lisp.yy.c:	lisp.lex
	flex -olisp.yy.c lisp.lex

lisp.tab.c:	lisp.y lisp.h
	bison -v lisp.y

comp:	comp.tab.c comp.yy.c
	$(CC) $(CFLAGS) -o comp comp.tab.c

comp.yy.c:	comp.lex
	flex -ocomp.yy.c comp.lex

comp.tab.c:	comp.y comp.h
	bison -v comp.y

#
# Dependencies
#

#calc.tab.o:	calc.h lex.yy.c
#lex.yy.o:	

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -r $(INTERMEDIATE) core 2> /dev/null

realclean:	clean
	-/bin/rm -r $(EXECS) core 2> /dev/null
