: top2 2dup swap . . ;

\ the recursive approach
: gcd-recursive ( m n -- d ) recursive
        swap
        over
        mod
        dup
    0> if 
        \      cr ." remainder non0" .s
        gcd-recursive
    else
        drop   \ get rid of flag
    then
    \ unwind recursion 
    \      cr ." remainder is0" .s
;

\ the iterative approach
: gcd-iterative ( m n -- d )
    begin
        swap
        over
        cr ." loop for m mod n: " top2
        mod
        dup
    0= until
    drop             \ get rid of the flag
    \    .s          \ see stack if you want to observe
;

\ greatest common divisor top level function
: gcd ( m n -- d )
    \ swap m and n if n > m
    2dup
    < if swap then
    gcd-recursive
;

: gcd2 ( m n -- d )
    \ swap m and n if n > m
    2dup
    < if swap then
    gcd-iterative
;

." 873 333 gcd . outputs: "
873 333 gcd .
cr

see gcd

cr
." enter bye to exit or return to continue interpreter "
quit
