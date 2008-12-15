#!/usr/bin/perl

# John Reese
# 2005-11-30
#
# Outputs number of CLI arguments and the args

print "Size: ".@ARGV."\n";

foreach $a (@ARGV) {
	print $a."\n";
}
