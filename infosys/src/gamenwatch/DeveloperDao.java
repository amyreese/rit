package gamenwatch;

import java.sql.*;
import java.util.List;
import org.springframework.jdbc.core.*;

public class DeveloperDao
{
	/**
	 * Inner class for mapping database rows to Developer objects.
	 */
	public static class DeveloperRowMapper implements RowMapper
	{
		public Object mapRow( ResultSet row, int num ) throws SQLException
		{
			Developer d = new Developer();
			d.setId( row.getInt( "id" ) );
			d.setName( row.getString( "name" ) );
			d.setDescription( row.getString( "description" ) );
			return d;
		}
	}

	/**
	 * Return a single Developer with the given ID.
	 */
	public static Developer load( int id )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("developer") + 
			" WHERE id=? LIMIT 1";
		List<Developer> l = db.query( query, new Object[] { new Integer(id) }, new DeveloperRowMapper() );
		return ( l.size() > 0 ) ? l.get( 0 ) : null;
	}

	/**
	 * Insert or update a Developer object in the database.
	 */
	public static void save( Developer d )
	{
		DatabaseSchema db = new DatabaseSchema();

		if ( d.getId() == -1 ) {
			String query = "INSERT INTO " + db.table("developer") + " ( name, description ) " +
				" VALUES ( ?, ? ) ";
			db.update( query, new Object[] { d.getName(), d.getDescription() } );

			query = "SELECT MAX(id) FROM " + db.table("developer");
			d.setId( db.queryForInt( query ) );
		} else {
			String query = "UPDATE " + db.table("developer") + " SET name=?, description=? " +
				" WHERE id=? LIMIT 1";
			db.update( query, new Object[] { d.getName(), d.getDescription(), new Integer(d.getId()) } );
		}
	}

	/**
	 * Delete a Developer object from the database.
	 */
	public static void remove( Developer d )
	{
		if ( d.getId() != -1 ) {
			DatabaseSchema db = new DatabaseSchema();
			String query = "DELETE FROM " + db.table("developer") + 
				" WHERE id=? LIMIT 1";
			db.update( query, new Object[] { new Integer(d.getId()) } );
		}
	}

	/**
	 * Return a list of developers matching the input string.
	 */
	public static List<Developer> find( String name )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("developer") + 
			" WHERE name LIKE ? ";
		return db.query( query, new Object[] { name }, new DeveloperRowMapper() );
	}

	/**
	 * Return a list of developers containing the input string.
	 */
	public static List<Developer> findLike( String name )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("developer") +
			" WHERE name LIKE '%?%' ";
		return db.query( query, new Object[] { name }, new DeveloperRowMapper() );
	}
}
