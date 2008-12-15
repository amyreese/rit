-- multiple additions test, results should
--	update after subsequent "+"
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("4")
ulp("8")
ulp("+")
ulp("5")
ulp("2")
ulp("+")
-- 48 + 52 = 100
ulp("7")
ulp("6")
ulp("+")
-- 100 + 76 = 176
ulp("4")
ulp("1")
ulp("9")
ulp("=")
-- 176 + 419 = 595