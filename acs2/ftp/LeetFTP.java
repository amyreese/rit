/**
 * LeetFTP.java
 *
 * Version:
 *	 $Id: LeetFTP.java,v 1.7 2004/02/22 04:57:56 jmr8223 Exp $
 *
 * Revisions:
 *   $Log: LeetFTP.java,v $
 *   Revision 1.7  2004/02/22 04:57:56  jmr8223
 *    - Project complete (YAY!)
 *
 *   Revision 1.6  2004/02/22 03:06:40  jmr8223
 *    - completed server and client processes, uploads/downloads properly
 *
 *   Revision 1.5  2004/02/21 19:13:39  jmr8223
 *    - reworked GUI to have name server options bar, less tabs, and
 *   	a tranfer table at the bottom
 *    - implemented lists and event handling for user and file listings
 *
 *   Revision 1.3  2004/02/10 01:34:51  jmr8223
 *    - completed initial design requirements
 *
 *   Revision 1.2  2004/02/03 21:27:22  jmr8223
 *    - added GUI tab components
 *    - added basic calling routines for other classes
 *
 *   Revision 1.1  2004/02/03 02:19:39  jmr8223
 *    - initial commit
 *
 */

/**
 * Sets up the GUI and server threads
 *
 * @author John Reese
 */
 
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
 
public class LeetFTP extends Thread {
	
	/* Constants */
	
	private final int SERVER_PORT = 1337;  // I R L337!
	
	/* Class Variables and GUI Components */
	
	private String directory;				// Current workspace
	private String address;
	
	private LeetActive active;			// Connection to name server
	private LeetServ server;				// Threaded server model
	private LeetClient link;				// Threaded Client Model
	
	private JFrame clientFrame;			// main JFrame for client GUI
	
	private JMenuBar menuBar;				// Menu bar and subcomponents
	private JMenu fileMenu;					// File Menu
	private JCheckBoxMenuItem hostItem;
	private JCheckBoxMenuItem portItem;
	private JMenuItem exitItem;
	private JMenu helpMenu;					// Help Menu
	private JMenuItem aboutItem;
	private JMenuItem helpItem;
	
	private JTextField nameTextField;		// Name for connecting to name server
	private JTextField portTextField;		// Port for connecting to name server
	private JTextField serverTextField;	// Name Server Hostname
	private JButton connectButton;	// Connect / Disconnect from Name Service
	
	private JButton searchInit;			// Start a search
	private JComboBox searchType;		// Drop-down menu of file types
	private JTextField searchName;	// What we are searching for

	private JTabbedPane mainPanel;	// Main GUI with below panes as tabs
	
	private JPanel workspacePanel;	// Panel showing current workspace
	private JPanel userListPanel;		// Panel of currently connected victims
	private JPanel searchPanel;			// Panel allowing file searches
	private JPanel transferPanel;		// Panel of current transfers
	private JPanel optionPanel;			// Panel of stats for Home tab
		
	private JList workspaceList = new JList ( new DefaultListModel() );
	private JList userList = new JList ( new DefaultListModel() );
	private JList fileList = new JList ( new DefaultListModel() );
	private JList searchList = new JList ( new DefaultListModel() );
	
	private JTable transferTable;  	// Table to track current transfers

	/**
	 * Spawns server / keepAlive threads
	 *
	 * @param wksp - workspace directory
	 * @param svc_host - hostname for the name server
	 * @param svc_port - port number for the name server
	 */
	
	public LeetFTP ( String wksp, String svc_host, int svc_port ) {
		
		directory = wksp;
		serverTextField = new JTextField( svc_host, 10 );
		portTextField = new JTextField( ""+svc_port, 4 );
		nameTextField = new JTextField( "AIM-NuklearEclipse" );

		active = new LeetActive(svc_host,svc_port,SERVER_PORT);
		active.setUserName("quick");
		active.start();
		address = active.getAddress();
		active.running=false;
		
		link = new LeetClient();

		server = new LeetServ ( address, SERVER_PORT, directory );
		server.start();
				
	}
	
	/**
	 * Search for a file from all connected users
	 */

	private class SearchUsers extends Thread {

		public void run() {
			ArrayList users = active.getHosts();
			LeetClient client[] = new LeetClient[users.size()];

			searchList.removeMouseListener(mouseHandler);
			((DefaultListModel)searchList.getModel()).clear();
			((DefaultListModel)searchList.getModel()).ensureCapacity(1);
			((DefaultListModel)searchList.getModel()).addElement("Searching...");

			for ( int x = 0; x < client.length; x++ ) {
				String userInfo = (String)users.get(x);
				userInfo = userInfo.substring(userInfo.indexOf("@")+1);
				client[x] = new LeetClient(userInfo.substring(0,userInfo.indexOf(":")),
						Integer.parseInt(userInfo.substring(userInfo.indexOf(":")+1)),
						address, directory);
				client[x].setPasv(portItem.getState());
				client[x].command = "LIST";
				client[x].start();
			}

			try {	sleep(5000); } catch (InterruptedException e) { }

			ArrayList matchFiles = new ArrayList();
			for (int x = 0; x < client.length; x++) {
				if (client[x].getFiles() != null) {
					ArrayList files = client[x].getFiles();
					for (int y = 0; y < files.size(); y++) {
						String file = (String)files.get(y);
						if (file.indexOf(" ") != -1) {
							file = file.substring(0,file.indexOf(" "));
						}
						if (file.startsWith(searchName.getText())) {
							matchFiles.add(file + "@" + users.get(x));
						}
					}
				}
			}

			((DefaultListModel)searchList.getModel()).clear();
			((DefaultListModel)searchList.getModel())
						.ensureCapacity(matchFiles.size());

			for (int x = 0; x < matchFiles.size(); x++) {
				((DefaultListModel)searchList.getModel()).addElement(matchFiles.get(x));
			}

			searchList.addMouseListener(mouseHandler);
		}	
	}

	SearchUsers search;
		
	/**
	 * Handles menu events, such as exit, turning on/off the server,
	 * and access to the help / about features
	 */
	
	private class MenuHandler implements ActionListener {
		public void actionPerformed ( ActionEvent e ) {
		
			Object source = e.getSource();
			
			// (De)Activate the server
			if (source == hostItem) {
				if (hostItem.getState()) {
					server.running = true;
				}
				else {
					server.running = false;
					
				}
			}

			// Set Client Process to Use Port / Pasv
			if ( source == portItem) {
				link.setPasv(portItem.getState());
			}
			
			// Kill the program
			if (source == exitItem) {
				System.exit(0);
			}
			
			// Show the About Box
			if (source == aboutItem) {
			
				( new P2PFTP() ).start();
			
			}
			
			// Show the Help / FAQ
			if (source == helpItem) {
			
			JFrame helpFrame = new JFrame("LeetFTP Help");
			
			helpFrame.getContentPane().setLayout(new GridLayout(0,1));
			helpFrame.getContentPane().add( new JLabel("LeetFTP Help") );
			helpFrame.getContentPane().add( new JLabel("") );
			helpFrame.getContentPane().add( new JLabel("Use the Connect/Disconnect toggle button to connect and disconnect from the name server.") );
			helpFrame.getContentPane().add( new JLabel("Turn off hosting or disable passive connections from the 'File' menu.") );
			helpFrame.getContentPane().add( new JLabel("See the Ub3r-L337 creator by clicking 'About' via the 'Help' menu.") );
			helpFrame.getContentPane().add( new JLabel("Connect to other hosts and download files on the 'Server' tab:") );
			helpFrame.getContentPane().add( new JLabel(" - Double-click on users to view their files") );
			helpFrame.getContentPane().add( new JLabel(" - Double-click on files to download them to your workspace") );
			helpFrame.getContentPane().add( new JLabel("Search for files by typing in the search phrase and clicking 'Search':") );
			helpFrame.getContentPane().add( new JLabel(" - Double-click on found files to download them") );
			
			helpFrame.setSize(600,400);
			helpFrame.setLocationRelativeTo(null);
			helpFrame.setVisible(true);
			
			}
		}
	}

	/**
	 * Handle mouse events
	 */
	 
	private MouseListener mouseHandler = new MouseAdapter() {
		public void mouseClicked (MouseEvent e) {
			if (e.getSource() == userList && e.getClickCount() == 2) {
				int index = userList.locationToIndex(e.getPoint());
				if (index > -1) {
					String userInfo = (String)((DefaultListModel)
							userList.getModel()).get(index);
					link.running = false;
					userInfo = userInfo.substring(userInfo.indexOf("@")-1);
					link = new LeetClient(userInfo.substring(userInfo.indexOf("@")+1,
							userInfo.indexOf(":")),	Integer.parseInt(
							userInfo.substring(userInfo.indexOf(":")+1)), address, directory);
					link.setPasv(portItem.getState());
					link.command = "LIST";
					link.start();
				}
			}
			if (e.getSource() == fileList && e.getClickCount() == 2) {
				int index = fileList.locationToIndex(e.getPoint());
				if (index > -1) {
					String fileName = (String)((DefaultListModel)
							fileList.getModel()).get(index);
					if (fileName.indexOf(" ") > -1) {
						fileName = fileName.substring(0,fileName.indexOf(" "));
					}
					link.command = "RETR " + fileName;
					System.out.println(link.command);
				}
			}
			if (e.getSource() == connectButton) {
				if (connectButton.getText().equals("Disconnect")) {
					active.running = false;
					connectButton.setText("Connect");
				}
				else {
					active = new LeetActive( serverTextField.getText(),
							Integer.parseInt(portTextField.getText()), SERVER_PORT );
					active.setUserName(nameTextField.getText());
					active.start();
					connectButton.setText("Disconnect");
				}
			}
			if (e.getSource() == searchInit) {
				search = new SearchUsers();
				search.start();
			}	
			if (e.getSource() == searchList && e.getClickCount() == 2) {
				int index = searchList.locationToIndex(e.getPoint());
				if (index > -1) {
					String fileInfo = (String)((DefaultListModel)
							searchList.getModel()).get(index);
					link.running = false;
					String userInfo = fileInfo.substring(fileInfo.indexOf("@")+1);
					userInfo = userInfo.substring(userInfo.indexOf("@")-1);
					fileInfo = fileInfo.substring(0,fileInfo.indexOf("@"));
					link = new LeetClient(userInfo.substring(userInfo.indexOf("@")+1,
							userInfo.indexOf(":")),	Integer.parseInt(
							userInfo.substring(userInfo.indexOf(":")+1)), address, directory);
					link.setPasv(portItem.getState());
					link.command = "RETR " + fileInfo;
					link.start();
				}
			}
		}
	};
	
	
	/**
	 * Create the entire GUI from scratch
	 */
	
	private void createGUI () {
	
		clientFrame = new JFrame ( "LeetFTP" );
				
		// Allow program to exit gracefully
		
		clientFrame.addWindowListener(
			new WindowAdapter() {
				public void windowClosing( WindowEvent e ) {
					System.exit ( 0 );
				} 
			}
		);
		
		createTabs();
		createMenu();
		
		// Top Options Bar
		connectButton = new JButton("Connect");
			connectButton.addMouseListener(mouseHandler);

		optionPanel = new JPanel( new FlowLayout(FlowLayout.LEFT) );
		
		optionPanel.add( connectButton );
		optionPanel.add( new JLabel("Name Server Hostname") );
		optionPanel.add( serverTextField );
		optionPanel.add( new JLabel("Port #") );
		optionPanel.add( portTextField );
		optionPanel.add( new JLabel("UserName") );
		optionPanel.add( nameTextField );
		
		// Bottom Transfer Table
		
		transferTable = new JTable();
		transferPanel = new JPanel( new BorderLayout() );
		transferPanel.add( new JLabel("Current Transfers:"), BorderLayout.NORTH );
		transferPanel.add( transferTable );
		
		// Make the tab pane the GUI pane
		clientFrame.getContentPane().setLayout( new BorderLayout() );
		clientFrame.getContentPane().add( mainPanel );
		clientFrame.getContentPane().add( optionPanel, BorderLayout.NORTH );
		clientFrame.getContentPane().add( transferPanel, BorderLayout.SOUTH );
				
		// Set Client Window Properties	
		clientFrame.setSize(800,600);
		//clientFrame.setResizable(false);
		clientFrame.setLocationRelativeTo(null);
		clientFrame.setVisible(true);
	
	}
	
	/**
	 * Create the tabbed panels for the GUI
	 */
	
	private void createTabs() {
	
		// Create the tabbed pane
		mainPanel = new JTabbedPane(JTabbedPane.BOTTOM);
				
		// Create the various panels
		workspacePanel = new JPanel( new BorderLayout( ) );
		userListPanel = new JPanel( new BorderLayout( ) );
		searchPanel = new JPanel( new GridLayout( 0,2 ) );
						
		// Create the pieces of the workspace panel
		workspaceList.setLayoutOrientation(JList.VERTICAL_WRAP);
		workspacePanel.add( new JScrollPane (workspaceList) );
		workspacePanel.add( new JLabel("Local File Listing"), BorderLayout.NORTH);
		
		// Create the UserList tab
		JPanel labelPanel = new JPanel( new GridLayout(0,2) );
		labelPanel.add( new JLabel("Users Connected:") );
		labelPanel.add( new JLabel("Selected User's Files:") );
		
		JPanel listPanel = new JPanel ( new GridLayout(0,2) );
		listPanel.add( new JScrollPane ( userList ) );
		listPanel.add( new JScrollPane ( fileList ) );
		
		userList.addMouseListener(mouseHandler);
		fileList.addMouseListener(mouseHandler);
		
		userListPanel.add( labelPanel, BorderLayout.NORTH );
		userListPanel.add( listPanel, BorderLayout.CENTER );

		// Create Search Panel
		searchPanel = new JPanel ( new BorderLayout() );
		JPanel searchOpsPanel = new JPanel ( new FlowLayout(FlowLayout.LEFT) );
		searchName = new JTextField(20);
		searchInit = new JButton("Search");
			searchInit.addMouseListener(mouseHandler);
		String types[] = {"Image","Video","Audio","Any"};
		searchType = new JComboBox(types);
			searchType.setSelectedIndex(3);
		
		searchOpsPanel.add(new JLabel("Search String"));
		searchOpsPanel.add(searchName);
		searchOpsPanel.add(new JLabel("File Type"));
		searchOpsPanel.add(searchType);
		searchOpsPanel.add(searchInit);

		searchPanel.add(new JScrollPane(searchList));
		searchPanel.add(searchOpsPanel, BorderLayout.NORTH);
		
		// Add panels to the tab pane
		mainPanel.addTab( "Home", workspacePanel );
		mainPanel.addTab( "Server", userListPanel );
		mainPanel.addTab( "Search", searchPanel );
	}
	
	/**
	 * Create the menu bar for the GUI
	 */
	
	private void createMenu() {
		// Create menu bar
		menuBar = new JMenuBar();
		clientFrame.setJMenuBar(menuBar);
		
		// Create menus
		fileMenu = new JMenu ("File");
		helpMenu = new JMenu ("Help");
		
		// Add menus to bar
		menuBar.add(fileMenu);
		menuBar.add(helpMenu);
		
		// Create File Menu Items
		hostItem = new JCheckBoxMenuItem("Allow Uploads", true );
		portItem = new JCheckBoxMenuItem("Use Passive Mode", true );
		exitItem = new JMenuItem ("Exit");
		
		// Add Items to File Menu
		fileMenu.add(hostItem);	
		fileMenu.add(portItem);
		fileMenu.addSeparator();	
		fileMenu.add(exitItem);
		
		// Create Help Menu Items
		helpItem = new JMenuItem ("Help");
		aboutItem = new JMenuItem ("About LeetFTP");
		
		// Add Items to Help Menu
		helpMenu.add(helpItem);
		helpMenu.addSeparator();	
		helpMenu.add(aboutItem);
		
		// Create menu action handler and set it active
		MenuHandler menuHandler = new MenuHandler();
		
		hostItem.addActionListener(menuHandler);
		portItem.addActionListener(menuHandler);
		exitItem.addActionListener(menuHandler);
		helpItem.addActionListener(menuHandler);
		aboutItem.addActionListener(menuHandler);
	}

	private int updateCount = 0;
	
	public void updateGUI () {
		updateCount++;
		if ( active.updated || updateCount%5 == 0 ) {
			updateUserList();
		}
		
		if ( updateCount%5 == 0 ) {
			updateWorkspace();
		}
		
		if ( link.updated ) {
			updateFileList();
		}
		
		if ( updateCount > 2000 ) {
			updateCount = 0;
		}
	}

	/**
	 * Update the workspace's list of files
	 */
	
	private void updateWorkspace() {
		File home[] = (new File(directory)).listFiles();
		
		((DefaultListModel)workspaceList.getModel()).clear();
		((DefaultListModel)workspaceList.getModel()).ensureCapacity(home.length);

		for (int x = 0; x < home.length; x++) {
			((DefaultListModel)workspaceList.getModel()).addElement(home[x]);
		}

		
	}
	
	/**
	 * Update the list of connected users
	 */
	
	private void updateUserList() {
		ArrayList users = active.getHosts();
				
		((DefaultListModel)userList.getModel()).clear();
		((DefaultListModel)userList.getModel()).ensureCapacity(users.size());
		
		for (int x = 0; x < users.size(); x++) {
			((DefaultListModel)userList.getModel()).addElement(users.get(x));
		}
		//userList.ensureIndexIsVisible(users.size());

	}

	/**
	 * Update the list of files on remote host
	 */
	private void updateFileList() {
		ArrayList files = link.getFiles();

		((DefaultListModel)fileList.getModel()).clear();
		((DefaultListModel)fileList.getModel()).ensureCapacity(files.size());

		for (int x = 0; x < files.size(); x++) {
			((DefaultListModel)fileList.getModel()).addElement(files.get(x));
		}

		//fileList.ensureIndexIsVisible(files.size());
	}

	/**
	 * Start the thread and instantiate the GUI
	 */
	
	public void run () {
	
		createGUI();
		
		while (true) {
			updateGUI();
			try {
				sleep(1000);
			}
			catch ( InterruptedException e ) { }
		
		}
			
	}
	
}
