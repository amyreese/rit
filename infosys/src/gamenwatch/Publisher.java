package gamenwatch;

import java.util.*;

public class Publisher {

	private int id = -1; // -1 signifies object to INSERT
	private String name;
	private String description;

	public Publisher() { }
	public Publisher(String name) {
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
		return GameDao.findByPublisher( this );
	}
}
