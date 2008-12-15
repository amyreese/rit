
[ifdef] post-test-loop-marker
    post-test-loop-marker
[endif]
marker post-test-loop-marker

\ post-test loop in Forth

cr
." post-test is a post-test loop:"
cr

cr
." call the post-test word this way: 3 post-test"
cr

: post-test ( n -- )
    begin
    dup .       \ output a number counting down
    1 -		
    dup 0= until	\ ends the loop
    drop
 ;

see post-test
cr

3 post-test

cr
." calling the post-test word with -33 will cause an infinite loop!"
cr

\ -33 post-test      infinite loop

bye
