package gamenwatch;

import java.sql.*;
import java.util.List;
import org.springframework.jdbc.core.*;

public class PublisherDao
{
	/**
	 * Inner class for mapping database rows to Publisher objects.
	 */
	public static class PublisherRowMapper implements RowMapper
	{
		public Object mapRow( ResultSet row, int num ) throws SQLException
		{
			Publisher p = new Publisher();
			p.setId( row.getInt( "id" ) );
			p.setName( row.getString( "name" ) );
			p.setDescription( row.getString( "description" ) );
			return p;
		}
	}

	/**
	 * Return a single Publisher with the given ID.
	 */
	public static Publisher load( int id )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("publisher") + 
			" WHERE id=? LIMIT 1";
		List<Publisher> l = db.query( query, new Object[] { new Integer(id) }, new PublisherRowMapper() );
		return ( l.size() > 0 ) ? l.get( 0 ) : null;
	}

	/**
	 * Insert or update a Publisher object in the database.
	 */
	public static void save( Publisher p )
	{
		DatabaseSchema db = new DatabaseSchema();
		String publisherTable = db.table("publisher");

		if ( p.getId() == -1 ) {
			String query = "INSERT INTO " + publisherTable + " ( name, description ) " +
				" VALUES ( ?, ? ) ";
			db.update( query, new Object[] { p.getName(), p.getDescription() } );

			query = "SELECT MAX(id) FROM " + db.table("publisher");
			p.setId( db.queryForInt( query ) );
		} else {
			String query = "UPDATE " + publisherTable + " SET name=?, description=? " +
				" WHERE id=? LIMIT 1";
			db.update( query, new Object[] { p.getName(), p.getDescription(), new Integer(p.getId()) } );
		}
	}

	/**
	 * Delete a Publisher object from the database.
	 */
	public static void remove( Publisher p )
	{
		if ( p.getId() != -1 ) {
			DatabaseSchema db = new DatabaseSchema();
			String query = "DELETE FROM " + db.table("publisher") + 
				" WHERE id=? LIMIT 1";
			db.update( query, new Object[] { new Integer(p.getId()) } );
		}
	}

	/**
	 * Return a list of publishers matching the input string.
	 */
	public static List<Publisher> find( String name )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("publisher") + 
			" WHERE name LIKE ? ";
		return db.query( query, new Object[] { name }, new PublisherRowMapper() );
	}

	/**
	 * Return a list of publishers containing the input string.
	 */
	public static List<Publisher> findLike( String name )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("publisher") +
			" WHERE name LIKE '%?%' ";
		return db.query( query, new Object[] { name }, new PublisherRowMapper() );
	}
}
