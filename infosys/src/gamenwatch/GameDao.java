package gamenwatch;

import java.sql.*;
import java.util.List;
import org.springframework.jdbc.core.*;

public class GameDao
{
	/**
	 * Inner class for mapping database rows to Game objects.
	 */
	public static class GameRowMapper implements RowMapper
	{
		public Object mapRow( ResultSet row, int num ) throws SQLException
		{
			Game g = new Game();
			g.setId( row.getInt( "id" ) );
			g.setName( row.getString( "name" ) );
			g.setDescription( row.getString( "description" ) );
			g.setStatus( row.getString( "status" ) );
			g.setReleaseDate( row.getDate( "launch" ) );

			g.setPublisher( PublisherDao.load( row.getInt( "publisher_id" ) ) );
			g.setDeveloper( DeveloperDao.load( row.getInt( "developer_id" ) ) );
			g.setPlatforms( PlatformDao.findByGame( g ) );
			g.setGenres( GenreDao.findByGame( g ) );

			g.setProfitMade( row.getDouble( "profit" ) );
			g.setSales( row.getInt( "sales" ) );
			g.setImg( row.getString( "img" ) );

			return g;
		}
	}

	/**
	 * Return a single Game with the given ID.
	 */
	public static Game load( int id )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("game") + 
			" WHERE id=? LIMIT 1";
		List<Game> l = db.query( query, new Object[] { new Integer(id) }, new GameRowMapper() );
		return ( l.size() > 0 ) ? l.get( 0 ) : null;
	}
	
	
	/**
	 * Return a single Game with the given name.
	 * 
	 * @param	name	the name of the game to query
	 * @return	The list of games matching the given name, 
	 * 			null if no items were found
	 */
	public static List<Game> find( String name ) {
		// Create a reference to the database
		DatabaseSchema db = new DatabaseSchema();
		
		// Create a query call
		String query = "SELECT * FROM " + db.table("game") +
			" WHERE name LIKE ? ";
		
		// Query the database
		return db.query( query, new Object[] { name }, new GameRowMapper() );
	}
	
	public static List<Game> findLike( String name )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("game") +
			" WHERE name LIKE '%?%' ";
		
		return db.query( query, new Object[] { name }, new GameRowMapper() );
	}

	public static List<Game> allGames() {
		// Create a reference to the database
		DatabaseSchema db = new DatabaseSchema();
		
		// Create a query call
		String query = "SELECT * FROM " + db.table("game");
		
		// Query the database
		return db.query( query, new Object[] { }, new GameRowMapper() );
	}

	/**
	 * Insert or update a Game object in the database.
	 */
	public static void save( Game g )
	{
		DatabaseSchema db = new DatabaseSchema();
		if ( g.getId() == -1 ) {
			String query = "INSERT INTO " + db.table("game") + 
				" ( name, description, developer_id, publisher_id, status, launch, sales, profit, img ) " +
				" VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ? ) ";
			db.update( query, new Object[] { g.getName(), g.getDescription() , new Integer(g.getDeveloper().getId()), 
				new Integer(g.getPublisher().getId()), g.getStatus(), g.getReleaseDate(), 
				new Integer(g.getSales()), new Double(g.getProfitMade()), g.getImg() } );

			query = "SELECT MAX(id) FROM " + db.table("game");
			g.setId( db.queryForInt( query ) );
		} else {
			String query = "UPDATE " + db.table("game") + 
				" SET name=?, description=?, developer_id=?, publisher_id=?, status=?, launch=?, " +
				" sales=?, profit=?, img=? WHERE id=? LIMIT 1";
			db.update( query, new Object[] { g.getName(), g.getDescription() , new Integer(g.getDeveloper().getId()), 
				new Integer(g.getPublisher().getId()), g.getStatus(), g.getReleaseDate(), 
				new Integer(g.getSales()), new Double(g.getProfitMade()), new Integer(g.getId()), g.getImg() } );
		}
		PlatformDao.saveByGame( g );
		GenreDao.saveByGame( g );
	}

	/**
	 * Delete a Game object from the database.
	 */
	public static void remove( Game g )
	{
		if ( g.getId() != -1 ) {
			DatabaseSchema db = new DatabaseSchema();
			String query = "DELETE FROM " + db.table("game") + " WHERE id=? LIMIT 1";
			db.update( query, new Object[] { new Integer(g.getId()) } );
		}
		GenreDao.removeByGame( g );
		PlatformDao.removeByGame( g );
	}

	/**
	 * Find a list of Games by a given Developer.
	 */
	public static List<Game> findByDeveloper( Developer d )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("game") +
			" WHERE developer_id=? ";
		return db.query( query, new Object[] { new Integer(d.getId()) }, new GameRowMapper() );
	}

	/**
	 * Find a list of Games by a given Publisher.
	 */
	public static List<Game> findByPublisher( Publisher p )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("game") +
			" WHERE publisher_id=? ";
		return db.query( query, new Object[] { new Integer(p.getId()) }, new GameRowMapper() );
	}

	/**
	 * Find a list of Games by a given Genre.
	 */
	public static List<Game> findByGenre( Genre g )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT g.* FROM " + db.table("game") + " AS g " +
			" JOIN " + db.table("game_genre") + " AS r " +
				" ON g.id=r.game_id " +
			" WHERE r.genre_id=? ";
		return db.query( query, new Object[] { new Integer(g.getId()) }, new GameRowMapper() );
	}

	/**
	 * Find a list of Games by a given Platform.
	 */
	public static List<Game> findByPlatform( Platform p )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT g.* FROM " + db.table("game") + " AS g " +
			" JOIN " + db.table("game_platform") + " AS p " +
				" ON g.id=p.game_id " +
			" WHERE p.platform_id=? ";
		return db.query( query, new Object[] { new Integer(p.getId()) }, new GameRowMapper() );
	}

	/**
	 * Find a list of Games tracked by a given User.
	 */
	public static List<Game> findByUser( User u ) { return findByUser( u, 1 ); }
	public static List<Game> findByUser( User u, int type )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT g.* FROM " + db.table("game") + " AS g " +
			" JOIN " + db.table("user_game") + " AS u " +
				" ON g.id=u.game_id " +
			" WHERE u.user_id=? AND u.type=? ";
		return db.query( query, new Object[] { new Integer(u.getId()), new Integer(type) }, new GameRowMapper() );
	}

}
