/**
 * P2PFTP.java
 *
 * Version:
 *	 $Id: P2PFTP.java,v 1.6 2004/02/22 04:57:56 jmr8223 Exp $
 *
 * Revisions:
 *   $Log: P2PFTP.java,v $
 *   Revision 1.6  2004/02/22 04:57:56  jmr8223
 *    - Project complete (YAY!)
 *
 *   Revision 1.5  2004/02/22 03:06:40  jmr8223
 *    - completed server and client processes, uploads/downloads properly
 *
 *   Revision 1.4  2004/02/17 22:44:56  jmr8223
 *    - separated splash screen into seperate thread
 *   	so client GUI starts immediatly
 *
 *   Revision 1.1  2004/02/03 02:19:39  jmr8223
 *    - initial commit
 *
 */

/**
 * Peer-to-peer fileshare program based on the FTP standard
 *
 * @author John Reese
 */
 
import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
 
public class P2PFTP extends Thread{
	
	public void run() {
		ImageIcon splashImage = new ImageIcon("splash.jpg","");
		
		JWindow uber = new JWindow();
		
		JLabel splashText = new JLabel(splashImage);
		uber.getContentPane().add( splashText );
					
		uber.setSize(550,400);
		uber.setLocationRelativeTo(null);
		uber.setVisible(true);
		
		try {
			Thread.currentThread().sleep(5000);
		} catch ( Exception e ) { }
		
		uber.setVisible(false);
		uber = null;
	}
	
	public static void main (String args[]) {
	
		if ( args.length != 3 ) {
		
			// Smite the user for being dumb
		
			System.err.println("Usage: java P2PFTP workspace nameserver-address nameserver-port");
			System.exit(1);
		
		}
		
		else {
		
			// reward the user by giving a splash and starting the GUI
			
			( new P2PFTP() ).start();
		
			( new LeetFTP ( args[0], args[1], Integer.parseInt(args[2]) ) ).start();
			
		}
	
	}

}
