-- tests decimal functionality
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("9")
ulp("4")
ulp("1")
ulp(".")
ulp("7")
ulp("8")
ulp("6")
ulp(".")
ulp("1")
ulp("2")
ulp("3")
ulp("+")
ulp(".")
ulp("1")
ulp("1")
ulp("1")
ulp("=")
-- 941.786123 + 0.111 = 941.897123