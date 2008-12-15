#!/usr/bin/perl

# John Reese
# 2005-12-02
#
# Split /etc/passwd and find the highest userid & print it

open (FH,'/etc/passwd');

$high = 0; 

while (!eof(FH)) {
	$pl = readline (FH);
	@entry = split(/:/,$pl);

	if ($high < @entry[2]) {
		$high = @entry[2];
		@final = @entry;
	}
}

print $final[0]."\n";
