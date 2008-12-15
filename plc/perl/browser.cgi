#!/usr/bin/perl

# John Reese
# 2005-12-02
#
# Output basic user info

print "Hello, visitor from ".$ENV{HTTP_HOST}.".\n";
print "You are running the script ".$ENV{SCRIPT_FILENAME}.".\n";
$b = $ENV{HTTP_USER_AGENT};
#$b =~ s/[\/].*//;
print "You are running the ".$b." browser.\n";
print "The server administrator is ".$ENV{SERVER_ADMIN}.".\n";


