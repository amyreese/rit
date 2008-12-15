
\ use of wordlist mechanism

\ order shows the wordlist search order

." order is now: "
order
cr

wordlist constant mylist

\ this word stuffs the new wordlist into the search order

: add-mylist get-order nip mylist swap set-order ;

also add-mylist definitions

." mylist is now the compilation wordlist at the top "
cr

." order is now: "
order
cr

\ words will show the words in the definition wordlist
words
." words defined in the current wordlist: (should be none above)"
cr

." words defined in the current wordlist: (from tictactoe)"
cr
s" tictactoe.fs" included

words

cr

