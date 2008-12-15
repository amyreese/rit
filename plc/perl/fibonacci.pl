#!/usr/bin/perl

# John Reese
# 2005-11-30
#
# Print the fibonacci sequence 

$n = shift(@ARGV);

$a1 = 1;
$a2 = 1;

print "$a1 $a2 ";

for ($b = 0; $b < $n-2; $b++) {
	$a3 = $a1 + $a2;
	$a1 = $a2;
	$a2 = $a3;
	print "$a3 ";
}

print "\n";
