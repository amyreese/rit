#!/usr/bin/perl

# John Reese
# 2005-11-30
#
# Output /etc/passwd with # at the beginning of lines

open (FH,'/etc/passwd');

while (!eof(FH)) {
	$pl = readline (FH);
	print "#".$pl;
}
