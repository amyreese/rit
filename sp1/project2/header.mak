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
