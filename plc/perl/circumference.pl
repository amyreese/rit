#!/usr/bin/perl

# John Reese
# 2005-11-30
# 
# Take radius from STDIO and calc the circumference

sub circumference {
	$PI = 3.141592654;
	return 2 * $PI * shift(@_);

}

$r = readline STDIN;
$r =~ s/\n//;
print "The circumference of ".$r." is ".circumference($r).".\n";
