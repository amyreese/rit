/*
 * Account.java
 *
 * Version:
 *   $Id:$
 *
 * Revisions:
 *   $Log:$
 */

import java.io.*;

/**
 * A class representing the current state of a bank account.
 *
 * @author     James E Heliotis
 * @author     Paul Tymann
 */

public class Account implements Serializable {

    private String id;      // the account "number"
    private int balance;    // the current balance

    // Ctors

    /** 
     * Create an account with the given balance in dollars.
     *
     * @param    id         the account "number".
     * @param    balance    initial account balance in dollars.
     */

    public Account( String id, int balance ) {
	this.id = id;
	this.balance = balance;
    }

    /**
     * Create an account with a zero balance.
     *
     * @param    id    the account "number".
     */

    public Account( String id ) {
	this( id, 0 );
    }

    // Accessors

    /**
     * Return the account number.
     *
     * @return    the account "number".
     */

    public String getId() {
	return id;
    }

    /**
     * Return the current account balance.
     *
     * @return    the current account balance.
     */

    public int getBalance() {
	return balance;
    }

    // Mutators

    /**
     * Deposit the given number of dollars into the account.
     *
     * @param    amount    number of dollars to deposit into the account.
     */

    public void deposit( int amount ) {
	balance += amount;
    }

    /**
     * Withdraw the given number of dollars from the account if there
     * is a sufficient amount of money in the account.  A
     * RuntimeException will be thrown if the withdraw would cause the
     * account balance to become negative.
     *
     * @param    amount    number of dollars to withdraw from the account.
     *
     * @throws   RuntimeException   if the account balance becomes negative.
     */

    public void withdraw( int amount ) {
	int tentative = balance - amount;

	if ( tentative < 0 )
	    throw new RuntimeException( "Negative balance" );
	
	balance = tentative;
    }

    /**
     * Return a string representation of this account.
     *
     * @return    a string representation of this account.
     */

    public String toString() {
	return id + ":\t\t$" + String.valueOf( balance );
    }

} // Account
