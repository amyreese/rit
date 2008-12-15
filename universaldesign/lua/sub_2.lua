-- multiple subtraction test
-- 	results should update after subsequent "-"
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("4")
ulp("9")
ulp("4")
ulp("-")
ulp("6")
ulp("5")
ulp("-")
-- 494 - 65 = 429
ulp("7")
ulp("7")
ulp("-")
-- 429 - 77 = 352
ulp("1")
ulp("8")
ulp("7")
ulp("=")
-- 352 - 187 = 165