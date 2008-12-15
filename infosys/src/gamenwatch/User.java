package gamenwatch;

import java.util.*;

public class User {

	private int id = -1; // -1 signifies object to INSERT
	private String userName;
	private String firstName;
	private String lastName;
	private String address;
	private String email;

	public User() { }
	public User( String userName ) {
		this.userName = userName;
	}

	public int getId() {
		return id;
	}

	public void setId( int id ) {
		this.id = id;
	}

	public String getUserName() {
		return userName;
	}

	public void setUserName( String u ){
		userName = u;
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public String getAddress() {
		return address;
	}

	public void setAddress(String address) {
		this.address = address;
	}

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public List<Game> gamesTracked() {
		return GameDao.findByUser( this, 0 );
	}

	public List<Game> gamesOwned() {
		return GameDao.findByUser( this, 1 );
	}

	public List<User> friends() {
		return UserFriendsDao.findByUser( this );
	}
}
