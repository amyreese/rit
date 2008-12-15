import java.io.*;

/**
 * Checkout lane manager.
 * @author John Reese
 * @author Erik Mathesius
 */
public class Checkout {

	public static void main(String[] args) throws IOException {
		// Make sure we have input
		if ( args.length < 1 ) {
			usage();
			System.exit(2);
		}

		// Create our lanes
		int numLanes = Integer.parseInt(args[0]);
		Lane[] lanes = new Lane[numLanes];
		for(int i=0;i<numLanes;i++){
			lanes[i] = new Lane(i+1);
			lanes[i].start();
		}
		
		boolean running = true;

		BufferedReader input = new BufferedReader( new InputStreamReader( System.in ) );

		String lanePrompt = "Lane (1-" + numLanes + ")> ";
		String actionPrompt = "Action> ";

		int lane;
		String action;

		// Repeatedly get input until EOF or done.
		while(running){
			// Get lane selection
			System.out.print( lanePrompt );
			try {
				lane = Integer.parseInt( input.readLine() ) - 1;
			} catch( NumberFormatException e ) {
				System.err.println( "Invalid input." );
				continue;
			}

			// make sure user input is in valid range
			if ( lane < 0 || lane > numLanes-1 ) {
				System.err.println( "Invalid lane." );
				continue;
			}

			// Get lane action
			System.out.print( actionPrompt );
			action = input.readLine();

			// Send input to appropriate Lane
			lanes[lane].inputAction( action );
		}
	}

	public static void usage() {
		System.out.println( "Usage: java Checkout <lanes>" );
		System.out.println( "Usage: java -jar Checkout.jar <lanes>" );
	}
}
