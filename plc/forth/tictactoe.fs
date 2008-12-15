
[ifdef] tictactoe-marker
    tictactoe-marker
[endif]

marker tictactoe-marker

\ tic tac toe from Leo Brodie's Starting Forth

variable board 7 allot    \ why 7? allocation always adds one.

: clear board 10 0 fill ;

: square board + ;

: bar ." | " ;

: dashes cr 9 0 do ." -" loop cr ;

: .box  
    square c@ dup 0= if  2 spaces  else
              dup 1 = if  ." X "    else
                         ." O "    then then drop ;

: display 
    cr 9 0 do
        I if I 3 mod 0=  if  dashes else bar then then
        I .box  loop cr quit ;  \ quit prevents ok from appearing

: play  1- 0 max 8 min square C! ;

: x! 1 swap play display ;

: o! -1 swap play display ;

: tic-tac-toe cr ." usage: n x! n o!" clear display ;
