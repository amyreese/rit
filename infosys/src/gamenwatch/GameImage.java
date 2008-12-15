package gamenwatch;

import java.util.*;

public class GameImage {

	private int id = -1; // -1 signifies object to INSERT
	private int type;
	private byte[] image;

	public GameImage() { }

	public int getId() {
		return id;
	}
	
	public void setId( int id ) {
		this.id = id;
	}

	public int getType() {
		return type;
	}

	public void setType( int type ) {
		this.type = type;
	}

	public byte[] getImage() {
		return image;
	}

	public void setImage( byte[] image ) {
		this.image = image;
	}
}
