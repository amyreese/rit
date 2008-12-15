#!/bin/sh

#x testcase.sh
#
# James Heliotis
# 14 April 2003

# This script is used to test a program that does all its work on data
# through Standard I/O and command line arguments. The usage format is:
#
#	testcase.sh options application infile answerfile arg1..argn
#
#  options: 0 or more strings beginning with '-' and separated by spaces
#	-v	verbose mode; says "OK"/"not OK" on standard output
#	-d	If output does not match, run 'diff' to compare the output.
#	-b	Do not worry about extra blanks
#x testcase.sh: the name of this script (could change w/o changing script)
#  application: the name of the program to be tested
#  infile: the data to be sent to the application via standard input
#  answerfile: a copy of what should come out of the application on
# 	       standard output if the program is working correctly.
#  argi: the i_th argument on the command line
#x	(In shell scripts and in C/C++, the first argument has an
#x	 index of 1; the command itself has an index of 0.)

#
# Error exit codes:
#
Exit_OK=0
Exit_no_infile=1
Exit_no_answerfile=2
Exit_bad_args=3
Exit_no_match=10

Exit_assertion_failure=99

# EOH__MARKER

#
# See if this is just a cry for help. If so, print out the above comments.
#
if [ "$*" = "-h" ]; then
	sed -e '1,2d' -e '/EOH__MARKER/,$d' -e '/^#x/d' -e 's/^# *//' < $0 \
	   | more
	exit $Exit_OK
fi

#
# Preliminary check of argument list (accept solitary "-h")
#
if [ $# -lt 3 ]; then
	echo Usage: \
	    `basename "$0"` options application infile answerfile arg1..argn
	exit $Exit_bad_args
fi

#
# Scan options
#
verbose=false
do_diff=false
diff_cmd="diff"
more_options=true
while $more_options; do
	case $1 in
	-v*)
		verbose=true
		shift
		;;
	-d*)
		do_diff=true
		shift
		;;
	-b)
		diff_cmd="$diff_cmd -b"
		shift
		;;
	-*)
		echo "\"$1\": unknown option"
		exit $Exit_bad_args
		;;
	*)
		more_options=false;
		;;
	esac
done

#
# Now that we have removed options from the command line arguments,
# recheck that we have at least the minimal number left.
#
if [ $# -lt 3 ]; then
	echo Usage: \
	    `basename "$0"` options application infile answerfile arg1..argn
	exit $Exit_bad_args
fi

#
# Get the file names from the command line.
#
application=$1; shift
infile=$1; shift
answerfile=$1; shift

#
# Make sure the data files exist.
#
if [ ! -r $infile ]; then
	echo $infile does not exist! 1>&2
	exit $Exit_no_infile
fi

if [ ! -r $answerfile ]; then
	echo $answerfile does not exist! 1>&2
	exit $Exit_no_answerfile
fi

#
# Run the program
#
eval $application $* < $infile > /tmp/outfile.$$

#
# Test the results
#
if eval $diff_cmd $answerfile /tmp/outfile.$$ > /dev/null 2>&1; then
	exit_code=$Exit_OK
else
	exit_code=$Exit_no_match
fi

#
# If -v flag was set, make a statement about the success of the test.
#
if $verbose; then
	case $exit_code in
	$Exit_OK)
		echo OK
		;;
	$Exit_no_match)
		echo Not OK
		;;
	*)
		echo "Internal script error 1 in `basename "$0"`" 1>&2
		exit $Exit_assertion_failure
	esac
fi

#
# If -d flag is set, run the diff program on the output.
#
if $do_diff && test "$exit_code" = "$Exit_no_match"; then
	echo
	echo Differences: \"\<\" is program output\; \"\>\" is correct output
	echo =========================================================
	eval "$diff_cmd $answerfile /tmp/outfile.$$"
fi

#
# Get rid of the temporary output file.
#
/bin/rm /tmp/outfile.$$

#
# All done.
#
exit $exit_code

