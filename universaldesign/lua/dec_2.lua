-- tests decimal with no leading digits
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp(".")
ulp("1")
ulp("2")
ulp("3")
ulp("4")
ulp("5")
ulp(".")
ulp("6")
ulp("7")
ulp("8")
ulp("9")
ulp("+")
ulp(".")
ulp("1")
ulp("2")
ulp("3")
ulp("=")
-- 0.123456789 + 0.123 = 0.246456789