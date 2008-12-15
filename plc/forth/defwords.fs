[ifdef] defwords-marker
    defwords-marker
[endif]

marker defwords-marker

\ 40 slot array used for the array indexing defining word

create ary 40 cells allot

\ defining words example; defines word for next slot's address in ary

: def-next1
    create 1 cells ,    \ 1 cell is 4 bytes in gforth
    does> @ + ;         \ fetch the index and add it to what's on stk

def-next1 next1         \ next1 is simple indexer into an array

cr ." addresses of storage in the array ary: "

ary .  cr
ary next1 .  cr
ary next1 next1 .  cr
ary next1 next1 next1 .  cr

cr ." now lets put stuff in there with stuff-ary"

: stuff-ary
    ary 40 0 do next1 i over ! loop drop ;

: dump-ary
    cr ary 40 0 do next1 dup @ . loop drop ;

stuff-ary

cr ." now dump the stuff with dump-ary"

dump-ary

1023 ary next1 next1 next1 next1 !

dump-ary
