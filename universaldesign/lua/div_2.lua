-- multiple division test
--	result should update after subsequent "/"
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("1")
ulp("0")
ulp("2")
ulp("4")
ulp("/")
ulp("8")
ulp("/")
-- 1024 / 8 = 128
ulp("1")
ulp("6")
ulp("/")
-- 128 / 16 = 8
ulp("2")
ulp("=")
-- 8 / 2 = 4