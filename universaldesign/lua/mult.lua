-- basic multiplication test
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("4")
ulp("5")
ulp("6")
ulp("*")
ulp("2")
ulp("3")
ulp("=")
-- 456 * 23 = 10488