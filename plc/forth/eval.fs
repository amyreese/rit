: uber ." Uber!" ;
: cool ." Cool!" ;
: nifty ." Nifty!" ;

create nuke 3 cells allot
uber nuke 0 cells  !
cool nuke 1 cells  !
nifty nuke 2 cells  !

: eval nuke over cells + @ ;
