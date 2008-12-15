/**
 * LeetActive.java
 *
 * Version:
 *   $Id: LeetActive.java,v 1.6 2004/02/22 03:06:40 jmr8223 Exp $
 *
 * Revisions:
 *   $Log: LeetActive.java,v $
 *   Revision 1.6  2004/02/22 03:06:40  jmr8223
 *    - completed server and client processes, uploads/downloads properly
 *
 *   Revision 1.5  2004/02/21 19:12:02  jmr8223
 *    - finalized name server usage, passes back user names and ip
 *
 *   Revision 1.4  2004/02/18 03:56:44  jmr8223
 *    - allowed name server client to register and renew with server
 *    - allowed for client window to get list of hosts from LeetActive
 *
 *   Revision 1.2  2004/02/10 02:06:55  jmr8223
 *   *** empty log message ***
 *
 *
 */

import java.util.*;
import java.net.*;
import java.io.*;

/**
 * Keeps the connection the name server open and alive
 *
 * @author John Reese
 */
public class LeetActive extends Thread {

    private DatagramSocket nameServer;		// Connection to the name server
    private int portNum;			// Port number for local machine's server
    
		public boolean running=true;	// flag to disconnect
    public boolean updated;				// Marked true if host list updated
    private ArrayList hostList;		// List of other hosts connected
		private String userName;			// What you are connecting as

	/**
	 * Create a dead object
	 */
	public LeetActive () {
		updated = false;
	}

	/**
	 * Generic constructor for the name service interface
	 */
    public LeetActive ( String svc_host, int svc_port, int portNum ) {
		
		try {
			nameServer = new DatagramSocket();
			nameServer.setSoTimeout(3000);
			nameServer.connect(InetAddress.getByName(svc_host), svc_port);
		}
		catch ( Exception e ) { System.err.println("LA "+e); }
			this.portNum = portNum;	
			hostList = new ArrayList();
    }

	/**
	 * Method to keep the connection alive with the name server
	 */
    public void run() {
		boolean connected = false;
		int ticket = 0;
		int serial = -1;
		int time = 1000;
	
		DatagramPacket inPack = new DatagramPacket(new byte[1024], 1024);
		DatagramPacket outPack = new DatagramPacket(new byte[1024], 1024);
		
		ByteArrayOutputStream outBuf = new ByteArrayOutputStream();
		DataInputStream inData;
		DataOutputStream outData = new DataOutputStream( outBuf );		
				
		while ( running ) {
			if ( !connected ) {		// Thoust ought Register thine self
				try {
					outBuf.reset();
					outData.writeByte(0);
					outData.writeUTF(userName);
					outData.writeInt(portNum);
					outData.flush();
					outPack.setData(outBuf.toByteArray());
					nameServer.send(outPack);
				}
				catch ( IOException e ) { System.err.println("LeetActive: "+e); }
			}
			else {					// Thoust ought Renew thine self
				try {
					outBuf.reset();
					outData.writeByte(2);
					outData.writeInt(ticket);
					outData.flush();
					outPack.setData(outBuf.toByteArray());
					nameServer.send(outPack);
				}
				catch ( IOException e ) { System.err.println(e); }
			}
			
			// Now we will receive a packet...
			try {
				nameServer.receive(inPack);
				inData = new DataInputStream (
							new ByteArrayInputStream(inPack.getData()));
							
				byte type = inData.readByte();
				
				if (type == 1) {		// Twas a ticket packet
					try {
						ticket = inData.readInt();
						if (ticket > -1) {		// Make sure its not evil
							connected = true;
						}
						else {
							connected = false;
						}
						time = inData.readInt();
					}
					catch ( IOException e ) { System.err.println(e); }
				}
				
				if (type == 5) {		// Twas an update packet
					try {
						int s = inData.readInt();
						if ( s > serial ) {		// Make sure its not old
							serial = s;	
							int size = inData.readInt();
							ArrayList newList = new ArrayList(size);
							
							for ( int x = 0; x < size; x++ ) {
								newList.add(new String("" + inData.readUTF() 
													 + "@" + inData.readUTF() 
													 + ":" + inData.readInt()));
							}
							
							if (!newList.equals(hostList)) {
								hostList = newList;
								updated = true;
							}
						}
					}
					catch ( IOException e ) { System.err.println(e); }
				}
			}
			catch ( SocketTimeoutException e ) {	// Server hates you
				connected = false; 
				System.err.println(e);
			}
			catch ( IOException e ) { System.err.println(e); }
			
			try {	// Take a nap
				sleep( time / 4 );
			}
			catch ( InterruptedException e ) {}
		}
    }
  
	public void setUserName(String name) {
		userName = name;
	}
	
  /**
   * Method to return the list of servers connected to the name service
   * 
   * @return hostList - List of hosts connected
	 */
	public ArrayList getHosts () {
		updated = false;
		return hostList;
	}

	public String getAddress () {
		while ( hostList.size() == 0 ) {
			try {
				sleep(100);
			}
			catch (InterruptedException e) { }
		}
		String name = "";
		String temp = "";
		for (int x = 0; x < hostList.size(); x++) {
			name = ((String)hostList.get(x));
			if (name.substring(0,userName.length()).equals(userName)) {
				temp = ((String)hostList.get(x)).substring(userName.length()+1);
			}
		}
		temp = temp.substring(0,temp.indexOf(":"));
		updated = true;
		hostList.clear();
		return temp.replace('.',',');
	}
}
