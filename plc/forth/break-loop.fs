
[ifdef] break-loop-marker
    break-loop-marker
[endif]
marker break-loop-marker

\ break loop in Forth

cr
." to implement a break loop, put the word leave at stop point. "
cr

\ break-loop emulates a break that skips loop body  

: break-loop ( n -- )
    1 ?do
    I dup 5 mod 0= if 
        drop ." breaking..." leave     \ ends the loop
    then
        . ." going..." 
    loop
 ;

cr
." break-loop is a loop with a break clause"
cr


see break-loop
cr

cr
." calling the break-loop word this way: 7 break-loop"
cr

7 break-loop

cr
quit
\ bye

