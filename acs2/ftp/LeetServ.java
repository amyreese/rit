/**
 * LeetServ.java
 * 
 * Version:
 *	 $Id: LeetServ.java,v 1.5 2004/02/22 03:06:40 jmr8223 Exp $
 *
 * Revisions:
 *   $Log: LeetServ.java,v $
 *   Revision 1.5  2004/02/22 03:06:40  jmr8223
 *    - completed server and client processes, uploads/downloads properly
 *
 *   Revision 1.4  2004/02/21 19:15:37  jmr8223
 *    - listens for connections, accepts user/pass commands, nothing else yet
 *
 *   Revision 1.2  2004/02/10 01:34:52  jmr8223
 *    - completed initial design requirements
 *
 *   Revision 1.1  2004/02/03 02:19:39  jmr8223
 *    - initial commit
 *
 */

/**
 * FTP server class that handles listening on the specified port for incoming
 * connections and queries
 *
 * @author
 */

import java.io.*;
import java.net.*;
import java.util.*;
 
public class LeetServ extends Thread {

	private String address; // User's IP Address
	private int port;					// Port to listen on
	private String directory; // Files to upload	
	public boolean running = true;	// Flag for server to die
			
	private List uploads;			// List of upload transfers

	/**
	 * Basic Constructor
	 *
	 * @param port - port number to listen on
	 */

	public LeetServ (String address, int port, String directory) {
		this.address = address;
		this.port = port;
		this.directory = directory;
	}
	
	/**
	 * Initialize server socket and spawn threads for each connection
	 */
	
	public void run () {
		ServerSocket listen;
		Socket newSock;
		LeetHost newHost;
		
		
		try {
			listen = new ServerSocket(port);
			while (true) {
				newSock = listen.accept();
				newHost = new LeetHost(newSock);
				newHost.start();
			}
		}
		catch ( SocketException e ) { System.err.println("LS:"+e); }
		catch ( IOException e ) { System.err.println(e); }
	}
	
	/**
	 * Share list of uploads with the client gui for display
	 *
	 * @return uploads - list of current upload transfers
	 */
	
	public List getUploads() {
		return uploads;
	}
	
	/**
	 * Class to handle FTP sessions, spawning off transfer threads
	 * as neccesary
	 */
	
	private class LeetHost extends Thread {
	
		private Socket client;				// connection to the client
		
		private BufferedReader input;		// Input stream from client
		private PrintWriter output;			// Output stream to client
	
		/**
		 * Basic Constructor for individual connections
		 *
		 * @param client - Socket to the connected client
		 */
	
		public LeetHost( Socket client ) {
			this.client = client;
			try {				
				input = new BufferedReader ( 
							new InputStreamReader ( client.getInputStream() ) );
				output = new PrintWriter ( client.getOutputStream(), true );
			}
			catch ( IOException e ) { System.err.println(e); }
		}
		
		/**
		 * Sets up communications with the client, spawning
		 * off transfers as requested
		 */
		
		public void run() {
			System.out.println("Connection attempt");
		
			String line;
			boolean verified = false;
			Socket data;

			if (!running) {
				output.println("421 Service Not Available");
			}
			else {
				System.out.println("Sending 220");
				output.println("220 Awaiting Input");
			
				try {
					boolean connected = true;
					boolean dataConn = false;
					Socket dataSock = null;
					String username = "";
					
					while (connected && (line = input.readLine()) != null) {
						System.out.println(username + " - " + line);
						String cmd = "    ";
						if (line.length() > 4) {
							cmd = line.substring(0,4).toUpperCase();
							line = line.substring(5);
						}
						else {
							cmd = line.toUpperCase();
							line = "";
						}

						if ( cmd.equals("USER") ) {
							username = line;
							output.println("331 User Name Accepted, Need password");
						} 
						else if ( cmd.equals("PASS") ) {
							output.println("230 User Authenticated");
							verified = true;
						}	
						else if ( ! verified ) {
							output.println("550 User Not Logged In");
						}

						else if ( cmd.equals("QUIT") ) {
							output.println("200 Goodbye!");
							client.close();
							connected = false;
						}
						else if ( cmd.equals("SYST") ) {
							output.println("215 UNIX - Gentoo v2.6.2");		
						}
						else if ( cmd.equals("TYPE") ) {
							System.out.println(line);
							output.println("200 Command OK");
						}
						else if ( cmd.equals("PASV") ) {
							ServerSocket pasvSock = new ServerSocket( port - 1 );
							pasvSock.setSoTimeout(30000);
							output.println("227 Going Passive (" + address + "," +
									((port-1)/256) + "," + ((port-1)%256) + ")");
							try {
								dataConn = true;
								dataSock = pasvSock.accept();
							}
							catch ( SocketTimeoutException e ) {
								output.println("550 Action Timed Out");
								dataConn = false;
							}
							pasvSock.close();
						}
						else if ( cmd.equals("PORT") ) {
							try {
								String ip = line.substring(line.indexOf(" ")+1);
								String addy[] = ip.split(",");
								ip = addy[0]+"."+addy[1]+"."+addy[2]+"."+addy[3];
								int port = Integer.parseInt(addy[4])/256 +
													 Integer.parseInt(addy[5])%256;
								dataSock = new Socket(ip,port);
								dataConn = true;
								output.println("200 Data Connection Open");
							}
							catch ( UnknownHostException e ) { 
								output.println("425 Could not open Data Connection");
								dataConn = false;
							}
							catch ( IOException e ) { }
						}
						else if ( cmd.equals("LIST") ) {
							if (dataConn) {
								output.println("150 Data Connection Open, Starting Transfer");
								PrintWriter dataOut = new PrintWriter (
										dataSock.getOutputStream(), true);
								File path = new File(directory);
								File files[] = path.listFiles();
								for ( int x = 0; x < files.length; x++ ) {
									if (files[x].isFile()) {
										dataOut.println(files[x].getName());
									}
								}
								dataSock.close();
								dataConn=false;
								output.println("226 Closing Data Connection, List Complete");
							}
							else {
								output.println("425 No Data Connection, use PORT / PASV");
							}
						}
						else if ( cmd.equals("RETR") ) {
							if (dataConn) {
								System.out.println("FILE: "+line);
								File file = new File(directory+line);
								if (file.isFile()) {
									output.println("150 Data Connection Open, Starting Transfer");
									LeetSend trans = new LeetSend(file,dataSock);
									trans.run();
									dataSock.close();
									dataConn = false;
									output.println("226 Closing Data Connection, File COmplete");	
								}
								else {
									output.println("550 File Not Found");
								}
							}
							else {
								output.println("425 No Data Connection, use PORT / PASV");
							}
						}
						else if ( cmd.equals("") ) {
							
						}
						else {
							output.println("202 Command not supported, yet...");
							System.out.println("202");
						}
					}
				}
				catch ( IOException e ) { System.err.println(e); }
			}
			
		}

	}

	public static void main (String args[]) {
		LeetServ server = new LeetServ("127,0,0,1",5001,"/nuke/share/");
		server.start();
	}

}
