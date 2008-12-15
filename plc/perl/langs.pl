#!/usr/bin/perl

# John Reese
# 2005-11-30
#
# Work with and print a list of plc languages

@lang = ("perl","yacc","flex","bison","scheme","prolog");

push(lang,("c","php","java"));

print "Size: ".@lang."\n";
@lang = sort (@lang);
print "Values: ";


for ($x = 0; $x < @lang; $x++) {
	print ", " if $x > 0;
	print "'".@lang[$x]."'";
}

print "\n";
