-- Basic division test
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("9")
ulp("9")
ulp("/")
ulp("3")
ulp("3")
ulp("=")
-- 99 / 33 = 3