/*
 * LeetSend.java
 *
 * Version:
 *   $Id: LeetSend.java,v 1.5 2004/02/22 03:06:40 jmr8223 Exp $
 *
 * Revisions:
 *   $Log: LeetSend.java,v $
 *   Revision 1.5  2004/02/22 03:06:40  jmr8223
 *    - completed server and client processes, uploads/downloads properly
 *
 *   Revision 1.4  2004/02/21 19:17:30  jmr8223
 *    - completed file transfer process
 *
 *   Revision 1.2  2004/02/10 01:34:52  jmr8223
 *    - completed initial design requirements
 *
 *   Revision 1.1  2004/02/03 21:25:08  jmr8223
 *    - initial commit
 *
 */

import java.io.*;
import java.net.Socket;

/**
 *  Takes care of sending a file to or from another client
 *
 *  @author	John Reese
 */
public class LeetSend {

    DataInputStream input;
    DataOutputStream output;
		

    public LeetSend( Socket input, File output ) {
	    try {
				this.input = new DataInputStream ( input.getInputStream() );
				this.output = new DataOutputStream ( new FileOutputStream ( output ) );
      }
      catch ( Exception e ) { System.err.println(e); }
    }

    public LeetSend( File input, Socket output ) {
      try {
	      this.input = new DataInputStream ( new FileInputStream ( input ) );
  	    this.output = new DataOutputStream ( output.getOutputStream() );
      }
      catch ( Exception e ) { System.err.println(e); }
    }

    public void run() {
			int num;
			byte info[] = new byte[1024];
			try {
				while ( (num = input.read(info,0,1024)) != -1 ) {
					output.write(info,0,num);
					output.flush();
				}
			}
			catch ( IOException e ) {	}
    }
}
