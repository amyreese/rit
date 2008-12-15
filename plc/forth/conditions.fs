\ selection statements in Forth

cr
." selection in Forth is supported by if-then-else constructs"
cr

\ decisions

cr
." selection depends on conditional tests and 'flags'"
cr

." here is a conditional test that outputs a true flag: 2 2 = . "

cr
2 2 = .
cr

." and a conditional test that outputs a false flag: 2 33 = . "

cr
2 33 = .
cr

." like C, non-zero is also true, but Forth uses -1 as a flag. "
cr
." there are many other conditional tests besides just = "
cr

