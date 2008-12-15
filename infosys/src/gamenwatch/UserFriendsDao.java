package gamenwatch;

import java.sql.*;
import java.util.List;
import org.springframework.jdbc.core.*;

public class UserFriendsDao
{
	/**
	 * Inner class for mapping database rows to User objects.
	 */
	public static class FriendRowMapper implements RowMapper
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
	 * Get a list of Users who are friends of a given User.
	 */
	public static List<User> findByUser( User u )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("user") +
			" WHERE id IN " +
			" ( SELECT id FROM " + db.table("user_friends") +
				" WHERE user1=? ) ";
		return db.query( query, new Object[] { new Integer(u.getId()) }, new FriendRowMapper() );
	}

	/**
	 * Delete a list of User friends of a given User.
	 */
	public static void removeByUser( User u )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "DELETE FROM " + db.table("user_friends") +
			" WHERE user1=? OR user2=? ";

		db.update( query, new Object[] { new Integer(u.getId()), new Integer(u.getId()) } );
	}
}
