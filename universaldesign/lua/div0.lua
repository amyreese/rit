-- tests dividing by zero
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("8")
ulp("6")
ulp("7")
ulp("/")
ulp("0")
ulp("=")
-- NaN