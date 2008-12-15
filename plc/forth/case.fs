\ case statements in Forth

: grade ( n -- )
  dup . ." grade is "
  case 
	99 of ." A" endof
	88 of ." B" endof
	77 of ." C" endof
	66 of ." D" endof
	." beats me!"	\ this is the default
  endcase
  cr
;

99 grade cr
88 grade cr
87 grade cr
77 grade cr

cr
." case statement must have an exact match with the case"

cr
