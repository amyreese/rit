package gamenwatch;

import java.sql.*;
import java.util.List;
import java.util.ArrayList;
import org.springframework.jdbc.core.*;

public class GenreDao
{
	/**
	 * Inner class for mapping database rows to Genre objects.
	 */
	public static class GenreRowMapper implements RowMapper
	{
		public Object mapRow( ResultSet row, int num ) throws SQLException
		{
			Genre g = new Genre();
			g.setId( row.getInt( "id" ) );
			g.setName( row.getString( "name" ) );
			g.setDescription( row.getString( "description" ) );
			return g;
		}
	}

	/**
	 * Return a single Genre with the given ID.
	 */
	public static Genre load( int id )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("genre") + 
			" WHERE id=? LIMIT 1";
		List<Genre> l = db.query( query, new Object[] { new Integer(id) }, new GenreRowMapper() );
		return ( l.size() > 0 ) ? l.get( 0 ) : null;
	}

	/**
	 * Insert or update a Genre object in the database.
	 */
	public static void save( Genre d )
	{
		DatabaseSchema db = new DatabaseSchema();
		String genreTable = db.table("genre");

		if ( d.getId() == -1 ) {
			String query = "INSERT INTO " + genreTable + " ( name, description ) " +
				" VALUES ( ?, ? ) ";
			db.update( query, new Object[] { d.getName(), d.getDescription() } );

			query = "SELECT MAX(id) FROM " + db.table("genre");
			d.setId( db.queryForInt( query ) );
		} else {
			String query = "UPDATE " + genreTable + " SET name=?, description=? " +
				" WHERE id=? LIMIT 1";
			db.update( query, new Object[] { d.getName(), d.getDescription(), new Integer(d.getId()) } );
		}
	}

	/**
	 * Delete a Genre object from the database.
	 */
	public static void remove( Genre d )
	{
		if ( d.getId() != -1 ) {
			DatabaseSchema db = new DatabaseSchema();
			String query = "DELETE FROM " + db.table("genre") + 
				" WHERE id=? LIMIT 1";
			db.update( query, new Object[] { new Integer(d.getId()) } );
		}
	}

	/**
	 * Return a list of Genres matching the input string.
	 */
	public static List<Genre> find( String name )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("genre") + 
			" WHERE name LIKE ? ";
		return db.query( query, new Object[] { name }, new GenreRowMapper() );
	}

	/**
	 * Return a list of Genres containing the input string.
	 */
	public static List<Genre> findLike( String name )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("genre") +
			" WHERE name LIKE '%?%' ";
		return db.query( query, new Object[] { name }, new GenreRowMapper() );
	}

	/**
	 * Return a list of Genres for a given Game.
	 */
	public static List<Genre> findByGame( Game g )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("genre") + " AS g " +
			" JOIN " + db.table("game_genre") + " AS gg " +
				" ON g.id=gg.genre_id " +
			" WHERE gg.game_id=? ";
		return db.query( query, new Object[] { new Integer(g.getId()) }, new GenreRowMapper() );
	}

	/**
	 * Update the list of Genres for a Game.
	 */
	public static void saveByGame( Game g )
	{
		removeByGame( g );

		DatabaseSchema db = new DatabaseSchema();
		String query = "INSERT INTO " + db.table("game_genre") +
			" ( game_id, genre_id ) VALUES ";

		boolean first = true;
		List<Genre> genres = g.getGenres();
		List<Object> params = new ArrayList( 2 * genres.size() );
		for ( Genre r : genres ) {
			if ( !first ) {
				query += ", ";
			}
			query += "( ?, ? )";
			params.add( new Integer( g.getId() ) );
			params.add( new Integer( r.getId() ) );
			first = false;
		}

		db.update( query, params.toArray() );
	}

	/**
	 * Remove all Genres related to a Game.
	 */
	public static void removeByGame( Game g )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "DELETE FROM " + db.table("game_genre") +
			" WHERE game_id=? ";
		db.update( query, new Object[] { new Integer(g.getId()) } );
	}
}
