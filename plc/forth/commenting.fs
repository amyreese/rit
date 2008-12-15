\ file name: commenting.fs
\ your name: Ben Steele
\ your login: bks
\ description:  --- starts a multi-line comment block on the file
\ this example of commenting contains one word, the-top, that outputs
\ the top of the stack without changing it.

\ marker section is optional.
\ you may find it useful while you are developing however.
\ the marker stuff is what let's you forget words in gForth and
\ that means you won't get the 'redefined' messages when you
\ reload the file.

[ifdef] optional-marker
    optional-marker
[endif]
marker optional-marker

\ minimum 1 liner above the start of the word definition
\ the-top outputs the top of the stack without changing it.

: the-top ( n -- n )     \ stack comment is stack view before -- after
  dup  . \ comments on what's happening
;

\ at end of file, do nothing to stay in interpreter
\ or add bye word to stop and exit gforth
