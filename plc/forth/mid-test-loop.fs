
[ifdef] mid-test-loop-marker
    mid-test-loop-marker
[endif]
marker mid-test-loop-marker

\ mid-test loop in Forth

cr
." echo is a mid-test loop that stops based on user input "
cr

cr
." call the echo word this way: 16 2 echo"
cr

\ note: for the next item, we need storage for input string data
\ here is a storage allocation called a 'spot' (silly name)

create spot 80 allot

\ loop with mid-point test

: echo ( c-adr -- )  	\ echo user input until an empty line
    begin		\ starts a loop
        dup 80 accept	\ gets input into buffer; leaves char count
    dup 0> while	\ test is in the middle here
        cr over swap type cr
    repeat		\ ends the loop
    2drop
 ;

see echo
cr

." call the echo word this way: spot echo"
." then type anything you want and echo will echo until input is empty"
cr
spot echo

cr
bye

