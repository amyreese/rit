-- tests +/- for basic functionality
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("1")
ulp("2")
ulp("3")
ulp("+/-")
ulp("+")
ulp("1")
ulp("2")
ulp("3")
ulp("=")
-- -123 + 123 = 0