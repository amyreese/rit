package gamenwatch;

import java.sql.*;
import java.util.List;
import org.springframework.jdbc.core.*;

public class UserDao
{
	/**
	 * Inner class for mapping database rows to User objects.
	 */
	public static class UserRowMapper implements RowMapper
	{
		public Object mapRow( ResultSet row, int num ) throws SQLException
		{
			User u = new User();
			u.setId( row.getInt( "id" ) );
			u.setUserName( row.getString( "username" ) );
			u.setFirstName( row.getString( "fname" ) );
			u.setLastName( row.getString( "lname" ) );
			u.setAddress( row.getString( "address" ) );
			u.setEmail( row.getString( "email" ) );
			return u;
		}
	}

	/**
	 * Return a single User with the given ID.
	 */
	public static User load( int id )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("user") + 
			" WHERE id=? LIMIT 1";
		List<User> l = db.query( query, new Object[] { new Integer(id) }, new UserRowMapper() );
		return ( l.size() > 0 ) ? l.get( 0 ) : null;
	}

	/**
	 * Insert or update a User object in the database.
	 */
	public static void save( User u )
	{
		DatabaseSchema db = new DatabaseSchema();
		String userTable = db.table("user");

		if ( u.getId() == -1 ) {
			String query = "INSERT INTO " + userTable + " ( username, fname, lname, address, email ) " +
				" VALUES ( ?, ?, ?, ?, ? ) ";
			db.update( query, new Object[] { u.getUserName(), u.getFirstName(), u.getLastName(),
				u.getAddress(), u.getEmail() } );

			query = "SELECT MAX(id) FROM " + db.table("user");
			u.setId( db.queryForInt( query ) );
		} else {
			String query = "UPDATE " + userTable + " SET username=?, fname=?, lname=?, address=?, email=? ) " +
				" WHERE id=? LIMIT 1 ";
			db.update( query, new Object[] { u.getUserName(), u.getFirstName(), u.getLastName(),
				u.getAddress(), u.getEmail(), new Integer(u.getId()) } );
		}
	}

	/**
	 * Delete a User object from the database.
	 */
	public static void remove( User u )
	{
		if ( u.getId() != -1 ) {
			DatabaseSchema db = new DatabaseSchema();
			String query = "DELETE FROM " + db.table("user") + 
				" WHERE id=? LIMIT 1";
			db.update( query, new Object[] { new Integer(u.getId()) } );
		}
		UserFriendsDao.removeByUser( u );
	}

	/**
	 * Return a list of Users matching the input string.
	 */
	public static List<User> find( String name )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("user") + 
			" WHERE username LIKE ? ";
		return db.query( query, new Object[] { name }, new UserRowMapper() );
	}

	public static List<User> allUsers()
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("user");
		return db.query( query, new Object[] { }, new UserRowMapper() );
	}

	/**
	 * Return a list of Users containing the input string.
	 */
	public static List<User> findLike( String name )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("user") +
			" WHERE username LIKE '%?%' ";
		return db.query( query, new Object[] { name }, new UserRowMapper() );
	}

	public static List<User> findByGame( Game g, int type )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT u.* FROM " + db.table("user") + " AS u " +
			" JOIN " + db.table("user_game") + " AS g " +
				" ON u.id=g.user_id " +
			" WHERE g.game_id=? AND g.type=? ";
		return db.query( query, new Object[] { new Integer(g.getId()), new Integer(type) }, new UserRowMapper() );
	}
}
