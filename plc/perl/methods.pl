#!/usr/bin/perl

# John Reese
# 2005-12-02
#
# outputs Java method declarations form all source
# files in the current directory

$dirname = '.';

opendir (DH,$dirname);
rewinddir (DH);

while ($dr = readdir(DH)) {
	next if $dr !~ /\S[.]java/;

	$class = $dr;
	$class =~ s/[.]java//;

	open (FH,$dr);

	while (!eof(FH)) {
		$fr = readline(FH); 
		next if $fr !~ /.*[(].*[)]/;

		print $dirname.".".$class.".".$fr;
	}
}
