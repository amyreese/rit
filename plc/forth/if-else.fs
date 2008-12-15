\ if else statements in Forth

cr
." selection in Forth is supported by if-then-else constructs"
cr

\ decisions

cr
." selection depends on conditional tests and 'flags'"
cr

." here is a conditional test that outputs a true flag: 2 2 = . "

2 2 = .
cr
cr

." and a conditional test that outputs a false flag: 2 33 = . "

2 33 = .
cr

." like C, non-zero is also true, but Forth uses -1 as a flag. "
cr
." there are many other conditional tests"
cr

: guess 
	dup 73 < if 	\ that's the not-so-secret number
		." You're low dude!" 
	else 
	73 > if 
		." You're HIGH!" 
	else 
		." SHEER GENIUS!" 
	then
	then ;

cr
." play the guessing game. Enter <number> guess to play"

1 guess

