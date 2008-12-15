package gamenwatch;

import java.sql.Date;
import java.util.*;
import java.io.Serializable;

public class Game implements Serializable {

	private int id = -1;
	private String name;
	private String description;
	private double rating;
	private String status;
	private Date releaseDate;
	private Developer developer;
	private Publisher publisher;
	private List<Platform> platforms;
	private List<Genre> genres;
	private double profitMade;
	private int sales;
	private String img;

	public Game() { }
	public Game(String name) {
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

	public void setDescription( String desc ) {
		description = desc;
	}

	public double getRating() {
		return rating;
	}

	public void setRating(double rating) {
		this.rating = rating;
	}

	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public List<Genre> getGenres() {
		return genres;
	}

	public void setGenres(List<Genre> genres) {
		this.genres = genres;
	}

	public Developer getDeveloper() {
		return developer;
	}

	public void setDeveloper(Developer developer) {
		this.developer = developer;
	}

	public Publisher getPublisher() {
		return publisher;
	}

	public void setPublisher(Publisher publisher) {
		this.publisher = publisher;
	}

	public double getProfitMade() {
		return profitMade;
	}

	public void setProfitMade(double profitMade) {
		this.profitMade = profitMade;
	}

	public int getSales() {
		return sales;
	}

	public void setSales(int sales) {
		this.sales = sales;
	}

	public Date getReleaseDate() {
		return releaseDate;
	}

	public void setReleaseDate(Date releaseDate) {
		this.releaseDate = releaseDate;
	}

	public List<Platform> getPlatforms() {
		return platforms;
	}

	public void setPlatforms(List<Platform> platforms) {
		this.platforms = platforms;
	}

	public String getImg() {
		return img;
	}

	public void setImg( String i ) {
		img = i;
	}
	
}
