
[ifdef] continue-loop-marker
    continue-loop-marker
[endif]
marker continue-loop-marker

\ continue loop in Forth

cr
." to implement a continue loop, put if statement around what to skip; "
cr

\ continue-loop emulates a continue that skips loop body  

: continue-loop ( n -- )
    1 do
    I dup 5 mod 0> if   \ use an if to check for continue
        .
    else
        drop
    then	\ wrap loop body to be skipped with an if statement
    loop
 ;

cr
." continue-loop is a loop with a continue clause"
cr

cr
." call the continue-loop word this way: 7 continue-loop"
cr


see continue-loop
cr

7 continue-loop

