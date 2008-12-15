
[ifdef] counted-loop-marker
    counted-loop-marker
[endif]
marker counted-loop-marker

\ counted loop in Forth

cr
." counted loops in Forth"
cr
." iota uses a counted loop:"
cr

: iota ( n2 n1 -- )  \ output n1 n1+1 ... n2-1 sequence of ints

    ?do 
        i . 
    loop
    cr
 ;

9 2 iota

cr
." call the iota word this way: 16 2 iota"
cr

see iota
cr

16 2 iota

cr
bye
