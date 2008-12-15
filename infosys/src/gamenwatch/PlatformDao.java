package gamenwatch;

import java.sql.*;
import java.util.List;
import java.util.ArrayList;
import org.springframework.jdbc.core.*;

public class PlatformDao
{
	/**
	 * Inner class for mapping database rows to Platform objects.
	 */
	public static class PlatformRowMapper implements RowMapper
	{
		public Object mapRow( ResultSet row, int num ) throws SQLException
		{
			Platform p = new Platform();
			p.setId( row.getInt( "id" ) );
			p.setSystemName( row.getString( "name" ) );
			p.setDescription( row.getString( "description" ) );
			return p;
		}
	}

	/**
	 * Return a single Platform with the given ID.
	 */
	public static Platform load( int id )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("platform") + 
			" WHERE id=? LIMIT 1";
		List<Platform> l = db.query( query, new Object[] { new Integer(id) }, new PlatformRowMapper() );
		return ( l.size() > 0 ) ? l.get( 0 ) : null;
	}

	/**
	 * Insert or update a Platform object in the database.
	 */
	public static void save( Platform p )
	{
		DatabaseSchema db = new DatabaseSchema();
		String platformTable = db.table("platform");

		if ( p.getId() == -1 ) {
			String query = "INSERT INTO " + platformTable + " ( name, description ) " +
				" VALUES ( ?, ? ) ";
			db.update( query, new Object[] { p.getSystemName(), p.getDescription() } );

			query = "SELECT MAX(id) FROM " + db.table("platform");
			p.setId( db.queryForInt( query ) );
		} else {
			String query = "UPDATE " + platformTable + " SET name=?, description=? " +
				" WHERE id=? LIMIT 1";
			db.update( query, new Object[] { p.getSystemName(), p.getDescription(), new Integer(p.getId()) } );
		}
	}

	/**
	 * Delete a Platform object from the database.
	 */
	public static void remove( Platform p )
	{
		if ( p.getId() != -1 ) {
			DatabaseSchema db = new DatabaseSchema();
			String query = "DELETE FROM " + db.table("platform") + 
				" WHERE id=? LIMIT 1";
			db.update( query, new Object[] { new Integer(p.getId()) } );
		}
	}

	/**
	 * Return a list of Platforms matching the input string.
	 */
	public static List<Platform> find( String name )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("platform") + 
			" WHERE name LIKE ? ";
		return db.query( query, new Object[] { name }, new PlatformRowMapper() );
	}

	/**
	 * Return a list of Platforms containing the input string.
	 */
	public static List<Platform> findLike( String name )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("platform") +
			" WHERE name LIKE '%?%' ";
		return db.query( query, new Object[] { name }, new PlatformRowMapper() );
	}

	/**
	 * Return a list of Platforms for a given Game.
	 */
	public static List<Platform> findByGame( Game g )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("platform") + " AS p " +
			" JOIN " + db.table("game_platform") + " AS gp " +
				" ON p.id=gp.platform_id " +
			" WHERE gp.game_id=? ";
		return db.query( query, new Object[] { new Integer(g.getId()) }, new PlatformRowMapper() );
	}

	/**
	 * Update the list of Platforms for a Game.
	 */
	public static void saveByGame( Game g )
	{
		removeByGame( g );

		DatabaseSchema db = new DatabaseSchema();
		String query = "INSERT INTO " + db.table("game_platform") +
			" ( game_id, platform_id ) VALUES ";

		boolean first = true;
		List<Platform> plats = g.getPlatforms();
		List<Object> params = new ArrayList( 2 * plats.size() );
		for ( Platform p : plats ) {
			if ( !first ) {
				query += ", ";
			}
			query += "( ?, ? )";
			params.add( new Integer( g.getId() ) );
			params.add( new Integer( p.getId() ) );
			first = false;
		}

		db.update( query, params.toArray() );
	}

	/**
	 * Remove the list of Platforms for a Game.
	 */
	public static void removeByGame( Game g )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "DELETE FROM " + db.table("game_platform") +
			" WHERE game_id=? ";
		db.update( query, new Object[] { new Integer(g.getId()) } );
	}
}
