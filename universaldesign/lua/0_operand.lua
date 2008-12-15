-- tests the use of no operands in a function
--	e.g. " / = ?" or "* = ?"
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("*")
ulp("=")
-- nothing should happen here: no state setting, no updating result
ulp("C")
ulp("/")
ulp("=")
-- same here