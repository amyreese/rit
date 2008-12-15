// $Id$
//
// Author: Jim Heliotis
//	(November 1991)

// Description:
//	A nice object component to make sure all instances get destroyed.
//
//	Just declare a Watcher in any class you want to monitor.
//
//      Normally, an instance of Watcher should be declared as a private
//      attribute of each class to be "watched", but inheritance of
//      the class also works.
//
//      To be guaranteed to work, no global (file scope) variables
//      containing a Watcher should be declared.
//

// Revisions:
//	$Log$

#ifndef _WATCHERH
#define _WATCHERH

#include <iostream>

using namespace std;

namespace RITCS {

  class Watcher {

  public:
    // report
    //
    // Report how many objects are currently in existence
    // that contain a Watcher.
    //
    static void report();

    // ctor
    //
    // A new watched object is being created.
    // Increment the object count.
    //
    Watcher();

    // dtor
    //
    // A watched object is being destroyed.
    // Decrement the object count.
    //
    ~Watcher();

    // Return the number of active watchers.
    //
    static int getActive();
	

  private:
    // watched object counter
    //
    static int active;
  };

  //
  //   A private support class
  //
  //
  //   The ShutDown class exists simply to cause something to execute
  //   as the program is shutting down. A single instance is delcared
  //   as a global (file scope) variable. When it is destroyed, it
  //   executes special code.
  //
  //   This class works in conjunction with the Watcher class to detect
  //   memory leaks.
  //
  //   Programmers should not use this class at all. They should use
  //   Watcher, which will automatically pull this class in as needed.
  //
  //   @see            Watcher
  //   @version        $Id: ShutDown.h,v 1.1 2002/08/09 18:23:48 jeh Exp $
  //   @author         James Heliotis
  //   @date           9 August 2002
  //

  class ShutDown {

  private: // creation

    // ctor
    //
    // This is only here to make the default constructor
    // inaccessible. Instances of this class are not to be created
    // by anyone else.
    //
    ShutDown();

    // dtor
    //
    // Report how many watched objects are left when this object
    // goes away. Hopefully, there are no global (file scope)
    // watched objects, or else this will not work.
    //
    ~ShutDown();

    friend int f(int); // to prevent compiler warning
	
  private: // instance

    // This class is set up as a singleton. No other instances
    // besides this internal one are created.
    //
    static ShutDown instance;

  };

} // namespace RITCS

#endif

