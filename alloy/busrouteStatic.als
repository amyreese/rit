/**
 * Bus Route/Schedule Project
 * Formal Methods: 2007-2, TR: 2-4PM
 * Chris Booth, John Reese, Kevin Tarchenski, Kyle Tirak
 */

//Libraries needed
open util/ordering[Times] as oo
open util/ordering[Step] as op


//*****The atoms included in the system*****


sig Passenger {
	destination : one Locations
}

sig Step{}

//States a bus can be in
sig BusStates {}
sig Transit extends BusStates {}
sig Stopped extends BusStates{
	place : one Locations
}


//A bus has:
// {one driver, a set of passengers, one route, a state }
sig Bus {
	passengers : set Passenger,
	route : one Routes,
	state : one BusStates// -> Step
} {
	//max capacity (set to 3 for testability)
	#passengers =< 3
}


//There is a set of peopel waiting at a location
sig Locations {
	waiters : set Passenger
}
one sig GleasonCircle, PerkinsGreen, ColonyManor, Crossroads, UC extends Locations {}


sig Stops {
	place : one Locations,
	time : one Times
}


//TODO::Flesh out routes, rename Route# and add more Routes
//TODO::give a route an order of stops
sig Routes {
//	stops : Locations -> Times
	stops : seq Stops
} {
	#stops > 1
}
//sig Route1 extends Routes {}


//TODO::Change names of Time# and get a list of all times
//TODO::Order the times
sig Times {}
//sig Time1, Time2 extends Times {}




//*********Predicates on the system**********
//Boarding
pred boardPassengers[ location : Locations, bus : Bus ]{
	//ensure there are people waiting at the location
	#(location.waiters) > 0
	
	//If at end of Route, loop back to beginning
	//bus.route.stops.last
}
run boardPassengers for 5

//Deboarding
//???????


//*********Facts constraining the system********
//A passenger is at exactly one place at any given time
fact passengerAtOnePlace {
	all p : Passenger | (one passengers.p && no waiters.p) || (one waiters.p && no passengers.p)
}

fact StopsAreUnique{
	all disj s1,s2 : Stops | (no s1.place & s2.place) || (no s1.time & s2.time)
}

fact StopsArePartOfRoutes{
	all s : Stops | some r : Routes | s in r.stops.elems
}

fact StopsAreNotInSameRouteTwice{
	all r : Routes | not r.stops.hasDups
}

fact LocationsAreStops{
	all l : Locations | some s : Stops | s.place = l
}

fact BusStopsAreOnRoute{
	all b : Bus | (b.state = Stopped) => (b.state.place in b.route.stops.elems.place)
}

fact RoutesHaveSomeBus{
	all r : Routes | some b : Bus | b.route = r
}

fact BusStatesHaveABus{
	all bs : BusStates | some b : Bus | b.state = bs
}

fact TimesHaveStops{
	all t : Times | some s : Stops | s.time = t
}

fact StopsHaveIncreasingTime{
	all s : Stops, r : Routes | ( (s in r.stops.elems) && (nextStop[r,s] != none) ) => (lt[s.time, nextStop[r,s].time])
}

//A stop has 

//***** Assertions *********/
assert BigAssertion {
	//max capacity for a bus is 3 passengers
	all bus : Bus | #(bus.passengers) <= 3
	
	//all passengers have exactly one destination
	all p : Passenger | one p.destination

	//A passenger can only be at one place at any given time
	all p : Passenger | (no passengers.p && one waiters.p) || (no waiters.p && one passengers.p)

	//all stops are unique
	all disj s1,s2 : Stops | (no s1.place & s2.place) || (no s1.time & s2.time)

	//Stops are part of a route
	all s : Stops | some r : Routes | s in r.stops.elems

	//Stops are not in same route twice
	all r : Routes | not r.stops.hasDups

	//Routes have at least 2 stops
	all r : Routes | #r.stops >= 2

	//Routes have at least one bus
	all r : Routes | some b : Bus | b.route = r

	//If a bus is stopped, it must be at exactly one location
	all b : Bus | (b.state = Stopped) => b.state.place in b.route.stops.elems.place

	//States need a bus
	all bs : BusStates | some b : Bus | b.state = bs

	//Times are times of Stops
	all t : Times | some s : Stops | s.time = t

	//Stops are in order by time
	all s : Stops, r : Routes | ( (s in r.stops.elems) && (nextStop[r,s] != none) ) => (lt[s.time, nextStop[r,s].time])
}

//Return the next stop if there is one
fun nextStop[route : Routes,stop : Stops]:Stops{
	let i = route.stops.idxOf[stop]{
		(stop = route.stops.last) => none else (route.stops[i + 1])
	}
	
}
check BigAssertion for 5

//errors?
pred test{
	one r : Routes | all s : Stops | (s in  r.stops.elems) => (s.place = UC)
}

run test for 6 but exactly 2 Routes
