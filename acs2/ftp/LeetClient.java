/**
 * LeetClient.java
 *
 * Version:
 *   $Id: LeetClient.java,v 1.3 2004/02/22 04:57:56 jmr8223 Exp $
 *
 * Revisions:
 *   $Log: LeetClient.java,v $
 *   Revision 1.3  2004/02/22 04:57:56  jmr8223
 *    - Project complete (YAY!)
 *
 *   Revision 1.2  2004/02/22 03:06:40  jmr8223
 *    - completed server and client processes, uploads/downloads properly
 *
 *   Revision 1.1  2004/02/21 19:14:39  jmr8223
 *    - hooks up to other ftp servers and gets listing and files properly
 *
 */

import java.util.*;
import java.net.*;
import java.io.*;

/**
 * Provides a connection to the remote FTP server for use by the 
 * LeetFTP GUI by returning a list of files on the remote system
 *
 * @author John Reese
 */

public class LeetClient extends Thread {
	private Socket server;
	private Socket data;
	private String host;
	private int port;
	private String address;
	private String directory;
	private boolean pasv;
	public String command;

	private ArrayList fileList;
	private BufferedReader input;
	private PrintWriter output;

	public boolean running = true;
	public boolean updated = false;
	
	public LeetClient () {
		updated = false;
	}
	
	public LeetClient (String host, int port, String address, String directory) {
		this.address = address;
		this.directory = directory;
		this.host = host;
		this.port = port;
	}

	public void run() {
		try {	
			server = new Socket(host, port);
			server.setSoTimeout(2000);

			input = new BufferedReader( new InputStreamReader (
					server.getInputStream() ) );
			output = new PrintWriter ( server.getOutputStream(), true );

			String reply = getReply();

			if (reply.substring(0,3).equals("220")) {
				while (!reply.substring(0,3).equals("230")) {
					output.println("USER nuke\r");
					reply = getReply();
					if (reply.substring(0,3).equals("331")) {
						output.println("PASS uber\r");
						reply = getReply();
					}
				}

				Socket data = null;

				while (running) {
					if (command.equals("")) {

					}
					else if (command.equals("LIST")) {
						data = goPasv(data);	
						BufferedReader dinput = new BufferedReader(
								new InputStreamReader(data.getInputStream()));
						output.println("LIST");
						String line;
						ArrayList newList = new ArrayList();
						while ( (line = dinput.readLine()) != null ) {
							String fileName = line;
							//if (fileName.indexOf(" ") == -1) {
							//	fileName = fileName.substring(0,fileName.indexOf(" "));
							//}
							System.out.println(fileName);
							newList.add(fileName);	
						}
						reply = getReply();
						if (reply.startsWith("226")) {
							System.out.println(reply);
						}
						else {
							System.out.println(reply);
						}
						fileList = newList;
						updated = true;

						command = "";
					}
					else if (command.substring(0,4).equals("RETR")) {
						String fileName = command.substring(5);
						data = goPasv(data);
						System.out.println(data);
						output.println(command);
						LeetSend trans = new LeetSend(data,new File(directory+fileName));
						trans.run();
						System.out.println("here");
						reply = getReply();
						command = "";
					}
					else if (command.equals("SYST")) {
						output.println("SYST");
						reply = getReply();
					}
					try {
						try {
							while (true) {
								System.out.println( input.readLine() );
							}
						}
						catch ( SocketTimeoutException e ) { } 
						sleep(2000);
					}
					catch (InterruptedException e) { }
				}
				
			}
			output.println("QUIT");
			getReply();
			server.close();
			
		}
		catch ( UnknownHostException e ) { System.err.println(e); }	
		catch ( SocketTimeoutException e ) { System.err.println(e); }
		catch ( IOException e ) { System.err.println(e); }
		catch ( Exception e ) { System.out.println(e); }

		fileList = null;
		updated = false;
	}

	private String getReply() {
		String reply = "";
		try {
			
			reply = input.readLine();
		
			if (reply != null && reply.substring(3,4).equals("-")) {
				String line;
				while ( ! (line = input.readLine()).substring(0,3)
										.equals(reply.substring(0,3))) {
					// This obliterates multi-line replies
				}
			}
		}
		catch ( IOException e ) { System.out.println(e); }
		return reply;
	}

	private Socket goPasv( Socket data ) {
		output.println("PASV");
		String reply = getReply();
		System.out.println(reply);
		String code = reply.substring(0,3);
		Socket newSock = null;
		if ( code.equals("125") || code.equals("150") ) {
			reply = getReply();
			System.out.println(reply);
		}
		if (code.equals("227")) {
			String ip = reply.substring(reply.indexOf("(")+1,reply.indexOf(")"));
			String addy[] = ip.split(",");
			try {
				ip = addy[0]+"."+addy[1]+"."+addy[2]+"."+addy[3];
				int port =Integer.parseInt(addy[4])*256 +Integer.parseInt(addy[5]);
				System.out.println(addy[4] + ":" + addy[5] + " - " + ip + ":" + port);
				newSock = new Socket(ip,port);
			}
			catch ( UnknownHostException e ) { 
				System.out.println("AIIYEEE!!!");
				newSock = null; 
			}
			catch ( IOException e ) { System.out.println(e); }
		}
		if (newSock == null) {
			try {
			newSock = new Socket(data.getInetAddress().getHostAddress()
					,data.getPort());
			System.out.println(newSock);
			} catch ( Exception e ) { System.out.println(e); }
		}
		return newSock;
	}

	public void setPasv( boolean p ) {
		pasv = p;
	}

	public synchronized ArrayList getFiles() {
		updated = false;
		return fileList;
	}

	public static void main (String args[]) {
		LeetClient ebb = new LeetClient("127.0.0.1",1337,"127.0.0.1","/nuke/");
		ebb.start();
	}

}
