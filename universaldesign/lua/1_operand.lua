-- tests the use of only 1 operand in a function
--	e.g. "4 / = ?" or "* 4 = ?"
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("1")
ulp("8")
ulp("*")
ulp("=")
-- equal sign shouldn't update result, no 2nd operand
ulp("C")
ulp("/")
ulp("1")
ulp("6")
ulp("/")
ulp("2")
ulp("=")
-- should be 16 / 2 = 8; first '/' shouldn't trigger state, no 1st operand