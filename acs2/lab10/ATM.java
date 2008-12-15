/*
 * ATM.java
 *
 * Version:
 *   $Id:$
 *
 * Revisions:
 *   $Log:$
 */

import java.io.*;
import java.net.*;

/**
 * ATM: provides user access to the bank via the network
 *
 * @author     James E Heliotis
 */

public class ATM {

    private static String readLine( BufferedReader in )
            throws java.io.IOException {
        String s = in.readLine();
        if ( s == null || s.length() < 1 ) {
            System.err.println( "No input! Exiting." );
            System.exit( 1 );
        }
        return s;
    }

    public static void main( String[] args ) {

        String host = null;
        int port = BankCodes.DEFAULT_PORT;

        // Handle command line arguments

        switch (args.length) {
        case 2:
            try {
                port = (new Integer( args[ 1 ] )).intValue();
            }
            catch( NumberFormatException e ) {
                System.err.println( "Non-numeric port!" );
                System.exit( 3 );
            }
        case 1:
            host = args[0];
            break;
        default:
            System.err.println( "Usage: " + "java ATM host [port]" );
            System.exit( 1 );
        }

        // Get ready to find out what the customer wants

        System.out.println( "Welcome to your bank!" );

        BufferedReader in = 
            new BufferedReader( new InputStreamReader( System.in ) );

        try {
            String s = null;

            // Get the account number

            System.out.print( "What is your account number? " );
            String account = readLine( in );

            // Do they want to deposit or withdraw?

            System.out.print( "Strike \"" + 
                              BankCodes.DEPOSIT + "\" for deposit, \"" + 
                              BankCodes.WITHDRAW + "\" for withdrawal: " );

            s = readLine( in );
            char command = s.charAt( 0 );

            // Find out how much money to deposit or withdraw

            switch ( command ) {
            case BankCodes.DEPOSIT:
                System.out.print( "How much do you wish to deposit: " );
                break;
            case BankCodes.WITHDRAW:
                System.out.print( "How much do you wish to withdraw: " );
                break;
            default:
                System.err.println( "Illegal choice. Sorry." );
                System.exit( 2 );
            }

            s = readLine( in );
            int amount = ( new Integer( s ) ).intValue();

            // Get ready to talk to the bank teller

            Socket conn = null;                 // Socket to the bank
            ObjectOutputStream net_out = null;  // Objects to the bank
            ObjectInputStream net_in = null;    // Objects from the bank

            // -----------------------------------------------------
            // ** The section below needs to be completed -- W.C. **
            // -----------------------------------------------------

            // Create the message that specifies the transaction

            // Connect to the bank server

            // Write the transaction out to the server

            // Wait for the reply.  Once it arrives store a reference
            // to the reply in the variable named confirmation

            BankMessage confirmation = null;

            // ------------------------------------------------------------
            // ** The rest of this program should not be changed -- W.C. **
            // ------------------------------------------------------------
            
            // Tell the user what happened

            if ( confirmation.getCommand() != BankCodes.SUCCESS ) {
                System.out.println( "The Bank did not accept your request." );

                switch ( confirmation.getCommand() ) {
                case BankCodes.BAD_COMMAND:
                    System.out.println(
                        "Internal error: Bad Command. Kill the programmer." );
                    break;
                case BankCodes.INSUFFICIENT_FUNDS:
                    System.out.println( "Insufficient Funds" );
                    break;
                case BankCodes.BAD_ACCOUNT_NUMBER:
                    System.out.println( "Bad Account Number" );
                    break;
                default:
                    System.out.println( 
                        "The reason \"" + confirmation.getCommand() +
                        "\" is unknown. Kill the programmer." );
                }
            }
            else {
                System.out.println( "Your new balance is $" + 
                                    confirmation.getAmount() );
            }

            // Done, clean up

            System.out.println( "Thank you for banking with us." );

            net_out.close();
            net_in.close();
            conn.close();
        }
        catch( NumberFormatException e ) {
             System.err.println( "Bad integer input: " + e );
        }
        catch( ClassNotFoundException e ) {
             System.err.println( "Malformed confirmation from Bank: " + e );
        }
        catch( java.io.IOException e ) {
             System.err.println( e );
        }
    }

} //ATM
