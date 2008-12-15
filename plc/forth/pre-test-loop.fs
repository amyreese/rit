
[ifdef] pre-test-loop-marker
    pre-test-loop-marker
[endif]
marker pre-test-loop-marker

\ pre-test loop in Forth

cr
." loops in Forth"
cr
." pre-test is a pre-test loop:"
cr

\ pre-test is like a while loop that tests the condition at the top

: pre-test ( n -- )
    begin
    dup 0> while	\ Forth's while clause 'floats' anywhere in a loop
        ." not zero yet" cr
        1 -		
    repeat		\ ends the loop
    drop
    ." zero now..." cr
 ;

cr
." call the pre-test word this way: 4 pre-test"
cr

see pre-test
cr

4 pre-test

cr
." call pre-test word with a negative number: -222 pre-test"
cr
-222 pre-test
cr
0 pre-test
bye
