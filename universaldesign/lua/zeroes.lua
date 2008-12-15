-- test trailing zeroes display
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("5")
ulp("0")
ulp("+")
ulp("5")
ulp("0")
ulp("+")
-- 50 + 50 = 100
ulp("1")
ulp("0")
ulp("0")
ulp("0")
ulp("0")
ulp("0")
ulp("0")
ulp("0")
ulp("=")
-- 100 + 10000000 = 10000100
ulp("C")
ulp("0")
ulp("0")
ulp("0")
ulp("0")
ulp("4")
ulp("0")
ulp("+")
ulp("0")
ulp("7")
ulp("=")
-- 40 + 7 = 47