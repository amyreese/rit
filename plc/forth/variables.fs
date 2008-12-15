[ifdef] variables-marker
	variables-marker
[endif]
marker variables-marker

\ variables

\ traditional way can combine assignment with elaboration
77 create x ,        \ x gets the value 77 stored in its locationa

\ newer way
variable y            \ 0 is stored under the hood

\ initialization or assignment of value to a name
44 x !
x
42 y !

\ dereferencing. Forth uses a REFERENCE MODEL.
x @ .
y @ .

