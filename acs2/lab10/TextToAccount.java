/*
 * TestAccounts.java
 *
 * Version:
 *   $Id: TextToAccount.java,v 1.1 2004/02/19 17:52:53 jmr8223 Exp $
 *
 * Revisions:
 *   $Log: TextToAccount.java,v $
 *   Revision 1.1  2004/02/19 17:52:53  jmr8223
 *    - initial commit
 *
 */

import java.util.*;
import java.io.*;

/**
 * Converts a .dat file of accounts into a serializable file
 *
 * @author   John Reese
 */

public class TextToAccount {

    // Storage for the accounts.

    private static Map accounts = new HashMap();

    /**
     * Creates accounts and stores them into the map.
     * Data for the accounts is taken from the file whose
     * name is given as a parameter.
     *
     * Note:  It is assumed that the data file is in the
     *        correct format.
     */

    private static void loadDatabase( String dbFilename ) {
        try {
	    // Let the tokenizer do the work

            StreamTokenizer in = 
		new StreamTokenizer( new FileReader( dbFilename ) );

	    // state == 0 means we are looking at an id,
	    // state == 1 means we are looking at a balance

	    int state = 0;

	    // temp variables required for parsing

	    String id = "";
	    int initBal = 0;

            while ( in.nextToken() != in.TT_EOF ) {
		switch ( state ) {
		case 0:              // process account number
		    id = in.sval;
		    break;
		case 1:              // process balance and create account
		    initBal = ( int )in.nval;
		    accounts.put( id, new Account( id, initBal ) );
		    break;
		}

		state = ( state + 1 ) % 2;
            }
        }
        catch( FileNotFoundException e ) {
            System.err.println( e );
            System.err.println( "No accounts were initialized. Sorry." );
            return;
        }
        catch( IOException e ) {
             System.err.println( "I/O Error: " + e );
        }
    }

    /**
     * The main method.  The program expects a single command line
     * argument that gives the name of the file that contains the
     * data that will be read by the program.
     *
     * @param    args    Command line arguments (name of file to read).
     */

    public static void main( String[] args ) {
	// Usage check

	if ( args.length != 1 ) {
	    System.err.println( "Usage:  java TestAccounts datafile" );
	    System.exit( 1 );
	}

        // Load the information

	loadDatabase( args[ 0 ] );

	// Print out the accounts.

	Iterator i = accounts.values().iterator();

	System.out.println( "Id\t\tBalance" );
	System.out.println( "--\t\t-------" );

	while ( i.hasNext() )
	    System.out.println( i.next() );
    }

} 
