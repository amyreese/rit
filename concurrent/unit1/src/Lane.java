import java.util.regex.*;

/**
 * Automated checkout Lane object.
 * @author John Reese
 * @author Erik Mathesius
 */
public class Lane extends Thread{
	private String action;
	private boolean updated;
	private int ID, totalCost, payment, items, refund, state;
	
	// Possible Lane states
	private final int SCANNING = 0;
	private final int PAYMENT = 1;
	private final int REFUND_ALL = 2;
	private final int COMPLETE_PAYMENT = 3;
	
	// Lane checkout limits
	private final int MAX_ITEMS = 5;
	private final int MAX_COST = 2;
	
	/**
	 * Initialize a new Lane object and set it's initial state.
	 * @param int ID for the lane
	 */
	public Lane(int ID){
		this.ID = ID;

		state = SCANNING;
		totalCost = 0;
		payment = 0;
		items = 0;
		refund = 0;
	}
	
	/**
	 * Pass an input action to the Lane object.
	 * @param String command action
	 */
	public void inputAction(String action){
		this.action = action;
		updated = true;

		while ( updated ) {
			Thread.currentThread().yield();
		}
	}
	
	/**
	 * Begin the Lane object's threaded execution loop.
	 */
	public void run(){
		boolean error;

		// Keep checking for an updated action and handle it.
		while(true){
			if(updated){
				error = input( action );

				// Bad input action
				if ( error ) {
					System.err.println( "Invalid input." );
				}

				updated = false;
			}
			this.yield();
		}
	}

	/**
	 * Handle an input action depending on the Lane object's current state.
	 * @param String command action
	 * @return boolean invalid input
	 */
	public boolean input( String action ) {
		Matcher m;

		if ( state == SCANNING ) {
			// 'scan' function
			m = Pattern.compile("scan\\s+(\\d+)").matcher(action);
			if( m.matches() ) {
				try {
					int cost = Integer.parseInt(m.group(1));
					scan(cost);
					return false;
				} catch ( NumberFormatException e ) {
					System.err.println("Invalid number format.");
				}
			}

			// 'reset' function
			m = Pattern.compile( "reset" ).matcher( action );
			if ( m.matches() ) {
				reset();
				return false;
			}
			
			// 'done' function
			m = Pattern.compile( "done" ).matcher( action );
			if ( m.matches() ) {
				done();
				return false;
			}

		} else if ( state == PAYMENT ) {
			// 'insert' function
			m = Pattern.compile( "insert\\s+(\\d+)" ).matcher( action );
			if ( m.matches() ) {
				try {
					int amount = Integer.parseInt( m.group(1) );
					insert( amount );
					return false;
				} catch ( NumberFormatException e ) {
					System.err.println("Invalid number format.");
				}
			}

			// 'pay' function
			m = Pattern.compile( "pay" ).matcher( action );
			if ( m.matches() ) {
				pay();
				return false;
			}

			// 'reset' function
			m = Pattern.compile( "reset" ).matcher( action );
			if ( m.matches() ) {
				reset();
				return false;
			}
			
		} else if ( state == REFUND_ALL ) {
			
		} else if ( state == COMPLETE_PAYMENT ) {
			
		}

		// Action not yet handled, must be malformed or incorrect
		return true;
	}
	
	/**
	 * Refund all.
	 * Calls refund() until the customers' payment is refunded
	 */
	public void refundAll(){
		while(payment>refund){
			if((payment-refund)>=5){
				refund(5);
			}else{
				refund(1);
			}
		}
	}
	
	/**
	 * Reset action.
	 * Return's the Lane object to starting state, refunding money if necessary.
	 */
	public void reset(){
		System.out.println("Lane" + ID + ":reset");
		if(state == PAYMENT && payment != 0){
			refundAll();
		}
		
		if(state == SCANNING || state == PAYMENT){
			state = SCANNING;
			totalCost = 0;
			payment = 0;
			items = 0;
			refund = 0;
		}
	}
	
	/**
	 * Scan action.
	 * Scan an item and adjust the Lane state appropriately.
	 * Will only proceed if the cost and items are within limits.
	 * @param int item cost
	 */
	public void scan(int cost){
		if ( items >= MAX_ITEMS ) {
			System.err.println( "Too many items." );
			return;
		}

		if ( cost > MAX_COST || cost < 1) {
			System.err.println( "Invalid item cost." );
			return;
		}

		totalCost += cost;
		items++;
		System.out.println("Lane" + ID + ":scan["+cost+"]");
	}
	
	/**
	 * Insert action.
	 * User can insert a 1 or 5 to pay for the items.
	 * @param int amount inserted (1 or 5)
	 */
	public void insert( int amount ) {
		if((amount==1 || amount==5) && payment<totalCost){
			payment+=amount;
			System.out.println("Lane" + ID + ":insert_"+amount);
		}else if(amount==1 || amount==5){
			System.err.println("You've already paid enough.");
		}else {
			System.err.println("Can only insert 1's and 5's.");
		}
	}
	
	/**
	 * Return action. (called refund because 'return' is reserved in Java)
	 * Return either 1 or 5 dollars to the user.
	 * @param int the amount refunded(1 or 5)
	 */
	public void refund( int amount ) {
		if(amount==1 || amount==5){
			refund+=amount;
			System.out.println("Lane" + ID + ":return_"+amount);
		} else {
			System.err.println("Error.");
		}
	}
	
	/**
	 * Done action.
	 * If the user has scanned at least one item, 'done' continues to the 
	 * next state, PAYMENT.
	 */
	public void done() {
		if(items>0){
			System.out.println("Lane" + ID + ":done");
			state = PAYMENT;
		}else{
			//TODO maybe we want to print an error message here?
		}
	}
	
	/**
	 * Pay action.
	 * If the user has inserted enough money to cover the cost of 
	 * all scanned items, then give appropriate change, and print
	 * a receipt for the transaction.
	 */
	public void pay() {
		if(payment>=totalCost){
			System.out.println("Lane" + ID + ":pay");
			
			state = COMPLETE_PAYMENT;

			while(payment-totalCost-refund>0){
				if((payment-totalCost-refund)>=5){
					refund(5);
				}else{
					refund(1);
				}
			}
			
			receipt();

			state = SCANNING;
			totalCost = 0;
			payment = 0;
			items = 0;
			refund = 0;
		}
	}
	
	/**
	 * Receipt action.
	 * Print the transaction cost, the amount tendered, and the change given.
	 */
	public void receipt(){
		System.out.println("Lane" + ID + ":receipt["+totalCost+"]["+payment+"]["+refund+"]");
	}
}
