package gamenwatch;

import java.util.*;

public class Developer {

	private int id = -1; // -1 signifies object to INSERT
	private String name;
	private String description;

	public Developer() { }
	public Developer(String name) {
		this.name = name;
	}

	public int getId() {
		return id;
	}
	
	public void setId( int id ) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription( String description ) {
		this.description = description;
	}

	public List<Game> games() {
		return GameDao.findByDeveloper( this );
	}
}
