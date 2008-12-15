--[[ 
automata.lua
Automata Simulator

@author John Reese
]]--

-- Get the next non-comment line
function nextLine()
	local line
	repeat
		line = inputLine()
		if line == nil then return nil end
	until string.sub(line, 1, 1) ~= "/"
	return line
end

-- Create a new Machine object
m = Machine:new()

-- Let's get the alphabet, first non-comment line
line = nextLine()
if line == nil then return nil end
tokens = tokenize(line)
for k,v in pairs(tokens) do
	if ( not m:addSymbol(v) ) then Machine:error("Incorrect machine definition.") end
end

-- Let's pull out states and transitions until the first # symbol
states = {}
while true do
	line = nextLine()
	if line == nil then return nil end
	tokens = tokenize(line)
	if (string.sub(tokens[1], 1, 1) == "#") then break end

	starting = false
	accepting = false
	name = ""
	symbol = ""
	destination = ""
	read = ""
	write = ""

	i = 0;

	-- Fill in appropriate values from input tokens
	for k,v in pairs(tokens) do
		i = i + 1

		if (v == ">" and i == 1) then
			starting = true
		elseif (v == "<" and i == 1) then 
			accepting = true
		else
			-- Fill in values based on order
			if (name == "") then
				name = v
			elseif (symbol == "") then
				symbol = v
			elseif (destination == "") then
				destination = v
			elseif (read == "") then
				read = v
			elseif (write == "") then
				write = v
			else
				-- error: too much input
				Machine:error("Incorrect machine definition.")
			end
		end
	end

	-- Error checking
	if (symbol ~= "" and destination == "") then
		Machine:error("Incorrect machine definition.")
	end

	-- Send information to the Machine
	if (name ~= "") then -- state defined
		if (states[name] ~= name) then -- state not yet added
			if ( not m:addState(name, accepting, starting) ) then Machine:error("Incorrect machine definition.") end
			states[name] = name
		else -- state modified
			if (starting) then
				if ( not m:setStarting(name) ) then Machine:error("Incorrect machine definition.") end
			end
			if (accepting) then
				if ( not m:setAccepting(name) ) then Machine:error("Incorrect machine definition.") end
			end
		end

		-- Define transition
		if (symbol ~= "" and destination ~= "") then
			if (states[destination] ~= destination) then -- state not yet added
				if ( not m:addState(destination) ) then Machine:error("Incorrect machine definition.") end
				states[destination] = destination
			end
			
			if ( not m:addTransition(name, destination, symbol, read, write) ) then Machine:error("Incorrect machine definition.") end

		end
	else
		-- error not enough input
		Machine:error("Incorrect machine definition.") 
	end

end 

-- Debug output
--m:dumpMachine()
--m:setDebug(1)

-- Now let's start polling for strings to test
while true do
	line = inputLine()
	if line == nil then break end

	if m:accepts(line) then
		print ( "Accepted." )
	else
		print ( "Rejected." )
	end
end


