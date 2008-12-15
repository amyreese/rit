/**
 * Bus Route/Schedule Project
 * Formal Methods: 2007-2, TR: 2-4PM
 * Chris Booth, John Reese, Kevin Tarchenski, Kyle Tirak
 */

//Libraries needed
open util/ordering[Times] as oo
open util/ordering[Step] as op


//*************************************************************//
//*****The atoms included in the system*****


sig Passenger {
	destination : one Locations
}

sig Step{}

//States a bus can be in
abstract sig BusStates {
	//Stop is the time and place of either:
	// the current place we are at if the bus is in the Stopped state
	// the last location we were at before being in the Transit state
	stop : one Stops
}
sig Stopped, Transit extends BusStates {}


//A bus has:
// { a set of passengers, one route, a state }
sig Bus {
	passengers : Passenger -> Step,
	route : one Routes,
	state : BusStates one -> Step
} {
	//max capacity (set to 3 for testability)
	#passengers.Step =< 3
}


//There is a set of people waiting at a location
abstract sig Locations {
	waiters : Passenger -> Step
}
one sig GleasonCircle, PerkinsGreen, ColonyManor, Crossroads, UC extends Locations {}


//Stops are a place at a perticular time.
// Disjoint stops can have both different: place & time or same: place OR time
sig Stops {
	place : one Locations,
	time : one Times
}


sig Routes {
	stops : seq Stops
} {
	#stops > 1
}


sig Times {}






//*************************************************************//
//*********Predicates on the system**********

//Boarding
//
//Takes a passenger from a location whose destination is in the bus' route, and puts
// them on the bus.  All other bus's and locations should remain the same
//
// Preconditions:
//	the bus is stopped at the location
// 	passenger is waiting at the bus' stop'd location during the step
//	the passenger is not waiting at their destination
//	the bus is not full
//	the bus is done deboarding
//
pred boardPassengers[ location : Locations, bus : Bus, pass : Passenger, step : Step ]{
	//ensure there are people waiting at the location
	pass in location.waiters.step
	pass.destination != location
	#bus.passengers.step < 3
	bus.state.step = Stopped
	bus.state.step.stop.place = location
	pass.destination in bus.route.stops.elems.place

	let step' = next[step]{
		location.waiters.step' = location.waiters.step - pass
		bus.passengers.step' = bus.passengers.step + pass

		all b : Bus | b.state.step' = b.state.step
		all b : Bus | b != bus => b.passengers.step' = b.passengers.step
		all loc : Locations | loc != location => loc.waiters.step' = loc.waiters.step
	}

}
run boardPassengers for 5





//Deboarding
//
//Takes a passenger from a bus and puts them at the location (waiting).
//  All other bus's and locations should remain the same
//
// Preconditions:
//	the bus is stopped at the passengers destination
//	
pred deboardPassenger[ bus : Bus, pass : Passenger, step : Step ] {
	bus.state.step = Stopped
	pass in bus.passengers.step
	bus.state.step.stop.place = pass.destination

	let step' = next[step], location = bus.state.step.stop.place {
		location.waiters.step' = location.waiters.step + pass
		bus.passengers.step' = bus.passengers.step - pass

		all b : Bus {
			b.state.step' = b.state.step
			(b != bus) => (b.passengers.step' = b.passengers.step)
		}
		all loc : Locations | loc != location => loc.waiters.step' = loc.waiters.step
	}
}
run deboardPassenger for 5




//startMoving
//
// Puts a bus in transit to its next stop.  All other bus's and 
//    locations should remain the same
//
// Preconditions:
//	the bus is stopped
//	the bus is either full, or there are no more passengers at the stopped
// 		location whose destinations are contained within the bus' route
//
pred startMoving[ bus : Bus, step : Step ]{
	bus.state.step = Stopped

	let location = bus.state.step.stop.place, waiters = location.waiters.step {
		#bus.passengers = 3 || 
		no waiters ||
		all p : Passenger {
			p in waiters => p.destination = location ||
			p in waiters => p.destination ! in bus.route.stops.elems.place
		}
	}	

	let step' = next[step] {
		bus.state.step' = Transit


		all b : Bus {
			b != bus => bus.state.step' = bus.state.step
			b.passengers.step' = b.passengers.step
		}
// no passengers with this line in, unknown issue
//		all loc : Locations | loc.waiters.step' = loc.waiters.step
	}
}

run startMoving for 5




//stopMoving
//
// Stops a moving bus at the next stop.  All other bus's and locations
//		should remain the same
//
// Preconditions:
//	bus is in transit
//
pred stopMoving[ bus : Bus, step : Step ]{
	bus.state.step = Transit

	let step' = next[step] {
		bus.state.step'.stop = nextStop[bus.route, bus.state.step.stop]
		bus.state.step' = Stopped

		all b : Bus {
			b != bus => bus.state.step' = bus.state.step
			b.passengers.step' = b.passengers.step
		}
// no passengers with this line in, unknown issue
//		all loc : Locations | loc.waiters.step' = loc.waiters.step
	}
}
run stopMoving for 5








//*************************************************************//
//*********Facts constraining the system********
//A passenger is at exactly one place at any given time
fact passengerAtOnePlace {
	all p : Passenger, step : Step | 
		(one passengers.step.p && no waiters.step.p) || 
		(one waiters.step.p && no passengers.step.p)
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
	all b : Bus, step : Step | 
b.state.step.stop.place in b.route.stops.elems.place
}

fact RoutesHaveSomeBus{
	all r : Routes | some b : Bus | b.route = r
}

fact BusStatesHaveABus{
	all bs : BusStates, step : Step | some b : Bus | b.state.step = bs
}

fact TimesHaveStops{
	all t : Times | some s : Stops | s.time = t
}

fact StopsHaveIncreasingTime{
	all s : Stops, r : Routes | ( (s in r.stops.elems) && (nextStop[r,s] != none) ) => 
		(lt[s.time, nextStop[r,s].time])
}

//A stop has 







//*************************************************************//
//***** Assertions *********/

//BigAssertion
//
// Checks all fact constraints on the system
//
assert BigAssertion {
	//max capacity for a bus is 3 passengers
	all bus : Bus, step : Step | #(bus.passengers.step) <= 3
	
	//all passengers have exactly one destination
	all p : Passenger | one p.destination

	//A passenger can only be at one place at any given time
	all p : Passenger, step : Step | 
		(no passengers.step.p && one waiters.step.p) || 
		(no waiters.step.p && one passengers.step.p)

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
	//If a bus is in transit, the last place it was at is in the route
	all b : Bus, step : Step | b.state.step.stop.place in b.route.stops.elems.place

	//States need a bus at every point in time
	all bs : BusStates, step : Step | some b : Bus | b.state.step = bs

	//Times are times of Stops
	all t : Times | some s : Stops | s.time = t

	//Stops are in order by time
	all s : Stops, r : Routes | ( (s in r.stops.elems) && (nextStop[r,s] != none) ) => (lt[s.time, nextStop[r,s].time])
}

check BigAssertion for 5





//*************************************************************//
//****** Functions *******//

//nextStop
//
//Return the next stop if there is one
//
fun nextStop[route : Routes,stop : Stops]:Stops{
	let i = route.stops.idxOf[stop]{
		(stop = route.stops.last) => none else (route.stops[i + 1])
	}
	
}















