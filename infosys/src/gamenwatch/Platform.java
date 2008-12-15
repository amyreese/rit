package gamenwatch;

import java.util.*;

public class Platform {

	private int id = -1; // -1 signifies object to INSERT
	private String systemName;
	private String description;

	public Platform() { }
	public Platform(String systemName) {
		this.systemName = systemName;
	}

	public int getId() {
		return id;
	}

	public void setId( int id ) {
		this.id = id;
	}

	public String getSystemName() {
		return systemName;
	}

	public void setSystemName(String systemName) {
		this.systemName = systemName;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription( String description ) {
		this.description = description;
	}

	public List<Game> games() {
		return GameDao.findByPlatform( this );
	}
}
