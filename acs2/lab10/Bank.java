/*
 * Bank.java
 *
 * Version:
 *   $Id:$
 *
 * Revisions:
 *   $Log:$
 */

import java.io.*;
import java.util.*;

/**
 * Bank: the repository of all accounts
 *
 * @author     James E Heliotis
 */

public class Bank {

    // The accounts are held here

    private Map accounts;

    // Ctors

    /** 
     * Create a bank with a place to keep accounts. 
     */

    public Bank() {
        accounts = new HashMap();
    }

    // Adding accounts

    /** 
     * Add a new account to the bank, given its number.  The
     * initial balance for the new account will be 0.  If an
     * account already exists with this id, a RunTimeException is
     * thrown.
     *
     * @param    id    the id number for this account
     *
     * @return   the account that was just created.
     *
     * @throws RunTimeException if the account already exists.
     */

    public Account newAccount( String id ) {

        Account newAcct = null;

        if ( exists( id ) )
            throw new RuntimeException( "Pre-existing account" );
        
        newAcct = new Account( id, 0 );
        accounts.put( id, newAcct );

        return newAcct;
    }

    // Accessing accounts

    /** 
     * Check if a specified account exists. 
     *
     * @param    id    the id of the account to check for.
     * 
     * @return   true if this account exists; otherwise return false.
     */

    public boolean exists( String id ) {
        return accounts.containsKey( id );
    }

    /** 
     * Return an account, given its id number.  A RunTimeException
     * will be thrown if the account does not exist.
     *
     * @param    id    the id of the account to be returned.
     *
     * @return   the account with the specified id.
     */

    public Account getAccount( String id ) {
        if ( !exists( id ) )
            throw new RuntimeException( "Non-existent account" );
        
        return (Account)accounts.get( id );
    }

    // Run the system

    /**
     * Start up the bank so that clients can manipulate their accounts.
     * One bank will be created with account information loaded from
     * a file.  A BankTeller will then be created to accept and process
     * requests from clients.
     *
     * The command line must contain the name of the file that contains
     * the initial account information.  A second, optional, command line
     * argument can be given to specify the port at which the teller
     * will listen for incoming connections.
     *
     * @param    args    Command line arguments (data file and port).
     */

    public static void main( String[] args ) {

        // Handle the command line

        int port = BankCodes.DEFAULT_PORT;

        switch (args.length) {
        case 1:
            break;
        case 2:
            try {
                port = ( new Integer( args[ 1 ] ) ).intValue();
                break;
            }
            catch( NumberFormatException e ) {
                // bad arg; go on to default
            }
            break;
        default:
            System.err.println( "Usage: " + "java Bank serializedData <port>" );
            System.exit( 1 );
        }

        // Create the bank

        Bank bank = new Bank();
        bank.loadDatabase( args[ 0 ] );

        BankTeller teller = new BankTeller( port, bank );
        teller.process();
    }

    private void loadDatabase( String dbFileName ) {
        try {
            // Create the Object Stream

            ObjectInputStream in =
                new ObjectInputStream( new FileInputStream( dbFileName ) );

            // Read in the accounts

            accounts = (Map)in.readObject();

            // Thats it!!

            in.close();
        }
        catch ( FileNotFoundException e ) {
            System.err.println( "PrintAccounts:  " + e.getMessage() );
        }
        catch ( ClassNotFoundException e ) {
            System.err.println( "Invalid file:  " + e );
        }
        catch ( IOException e ) {
            System.err.println( "I/O Error:  " + e );
        }

        if ( accounts == null )
            accounts = new HashMap();
    }

} // Bank
