-- multiple multiplication test
--	result should update after subsequent "*"
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("1")
ulp("2")
ulp("*")
ulp("3")
ulp("4")
ulp("*")
-- 12 * 34 = 408
ulp("2")
ulp("1")
ulp("*")
-- 408 * 21 = 8568
ulp("1")
ulp("2")
ulp("=")
-- 8568 * 12 = 102816