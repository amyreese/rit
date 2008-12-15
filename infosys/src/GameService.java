/**
* GameService.java
*
* Service class which provides various functionality relating to games
*/

import gamenwatch.*;
import java.util.*;
import java.sql.Date;

public class GameService {

	public GameService() { }

	/*
	* Get info on a specific game
	* Parameters: id - The id of the game
	*/
	public Game getGame( int id ) {

		Game g = GameDao.load(id);
				
		return g;
	}

	/*
	* Search for a game with the given name
	*/
	public List<Game> searchByName( String name ) {
		List<Game> results = null;
		if( name.equals("") || name == null ) {
			results = GameDao.allGames();
		} else {
			results = GameDao.find(name);
		}
		
		return results;
	}

	/*
	* Returns a list of users tracking a given game
	* Parameters: id - The id of the game to use
	*/
	public List<User> getUsers( int id ){

		// Make a test list of users to return
		// Eventually this will come through the GameDao
		List<User> users = UserDao.allUsers();

		return users;
	}

	/*
	* Returns a list of the current top tracked games, ordered by rank, descending.
	* Parameters: i - The number of games to return
	*/
	public List<Game> getTopTrackedGames( int i ) {
		
		List<Game> games = GameDao.allGames();

		return games;
	}

	/*
	* Return a list of games with a release date in the next month
	* Parameters: i - The number of games in the list
	*/
	public List<Game> getUpcomingGames( int i ) {

		List<Game> games = GameDao.allGames();

		return games;
	}

	/*
	* Return a list of games which were recently updated
	* Parameters: i - The number of games in the list
	*/
	public List<Game> getUpdatedGames( int i ) {

		List<Game> games = GameDao.allGames();

		return games;
	}

	/*
	* Return a list of similar games for a given game.
	* Parameters: i - The Id of the game to base the search on
	*/
	public List<Game> similarGames( int i ) {
		//Return a list of similar games

		return null;
	}

}
