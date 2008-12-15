-- basic subtraction test
-- @author Alek Demko

-- shortname copy of ul_press
ulp = ul_press

-- Initialize button delays
ul_setdelay(250)
ul_setcount(1)

-- Button testing
ulp("5")
ulp("7")
ulp("6")
ulp("4")
ulp("-")
ulp("8")
ulp("7")
ulp("3")
ulp("=")
-- 5764 - 873 = 4891