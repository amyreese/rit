
[ifdef] endless-loop-marker
    endless-loop-marker
[endif]
marker endless-loop-marker

\ endless loop in Forth

cr
." endless is a endless loop that waits for input forever (Ctl-C stops)"
cr

cr
." calling the endless word this way: spot endless"
cr

cr
\ endless loop can be terminated with control-c

: endless ( c-adr -- )  	\ echo user input forever
    begin		\ starts a loop
        dup 80 accept	\ gets input into buffer; leaves char count
        over swap type
    again		\ ends the endless loop
 ;


\ note: for the next item, we need storage for input string data
\ here is a storage allocation called a 'spot' (silly name)

create spot 80 allot

see endless
cr

spot endless

