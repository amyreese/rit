/*
 * BankTeller.java
 *
 * Version:
 *   $Id:$
 *
 * Revisions:
 *   $Log:$
 */

import java.net.*;
import java.io.*;

/**
 * BankTeller: the network interface to the Bank
 *
 * @author    James E Heliotis
 * @author    Paul Tymann
 */

public class BankTeller {

    private int port = 0;              // Accept connection at this port
    private Bank bank = null;          // The bank this teller works for
    ServerSocket serverSocket = null;  // The socket user by the teller

    /**
     * Create a new bank teller, accepting requests at the given
     * port, using the given bank.
     *
     * @param    port    the port where connections will be accepted.
     * @param    bank    the bank this teller works for.
     *
     */

    public BankTeller( int port, Bank bank ) {
        this.bank = bank;

        try {
            serverSocket = new ServerSocket( port );
        }
        catch ( IOException e ) {
            System.err.println("Could not listen on port: " + port + ".");
            System.exit(1);
        }
    }

    /**
     * The service loop for the teller.  Wait for a connection.
     * Service the requests provided by the client.  Close the
     * connection.
     */

    public void process() {

        BankMessage msg = null;

        // Forever (computer do not get breaks!!)

        while ( true ) {
            try {
                // Wait for an incoming connection

                Socket clientSocket = null;

                try {
                    clientSocket = serverSocket.accept();
                } catch (IOException e) {
                    System.err.println( "Accept failed." );
                    System.exit(1);
                }

                // Only BankMessages are exchanged between the client
                // and the teller.

                ObjectOutputStream out =
                      new ObjectOutputStream(
                           clientSocket.getOutputStream() );
                ObjectInputStream in =
                      new ObjectInputStream(
                           clientSocket.getInputStream() );

                // Service the customer

                boolean custDone = false;

                while ( !custDone ) {
                    try {
                        // Read a request

                        msg = ( BankMessage )in.readObject();

                        // If the account in the message exists, process
                        // the request.

                        if ( bank.exists( msg.getAccount() ) ) {
                            Account acct = bank.getAccount( msg.getAccount() );
                            int amt = msg.getAmount();

                            // Figure out what they want to do

                            switch ( msg.getCommand() ) {
                            case BankCodes.DEPOSIT:
                                acct.deposit( amt );

                                msg.setAmount( acct.getBalance() );
				msg.setCommand( BankCodes.SUCCESS );

                                System.out.println( "Teller: $" + amt +
                                                    " deposited to acct #" +
                                                    msg.getAccount() );
                                break;
                            case BankCodes.WITHDRAW:
                                if ( amt > acct.getBalance() ) {
                                    msg.setCommand( 
				        BankCodes.INSUFFICIENT_FUNDS );
                                }
                                else {
                                    acct.withdraw( amt );

                                    msg.setAmount( acct.getBalance() );
				    msg.setCommand( BankCodes.SUCCESS );

                                    System.out.println( "Teller: $" + amt +
                                                        " withdrawn from " +
                                                        "acct #" +
                                                        msg.getAccount() );
                                }
                                break;
                            default: // return same amount
                                msg.setCommand( BankCodes.BAD_COMMAND );
                            }
                        }
                        else {
                            msg.setCommand( BankCodes.BAD_ACCOUNT_NUMBER );
                        }
 
                        // Send back the results

                        out.writeObject( msg );
                    }
                    catch ( java.io.IOException e ) {
                        // Bad data => close connection
                        custDone = true;
                    }
                    catch ( java.lang.ClassNotFoundException e ) {
                        // hope for better data next time
                    }
                }

                // Release our resources

                out.close();
                in.close();
                clientSocket.close();
            }

            catch( IOException e ) {
                break; // TBD
            }
        }

        // Release the server socket

        try {
            serverSocket.close();
        }
        catch( IOException e ) {
            // do nothing; an error on close assumes socket already gone
        }
    }

} // BankTeller
