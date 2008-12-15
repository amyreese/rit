package gamenwatch;

import java.sql.*;
import java.util.List;
import org.springframework.jdbc.core.*;

public class GameImageDao
{
	public static class GameImageRowMapper implements RowMapper
	{
		public Object mapRow( ResultSet row, int num ) throws SQLException
		{
			GameImage i = new GameImage();
			i.setId( row.getInt( "id" ) );
			i.setType( row.getInt( "type" ) );
			Blob b = row.getBlob( "image" );
			i.setImage( b.getBytes( (long) 1, (int) b.length() ) );
			return i;
		}
	}

	public static GameImage load( int id )
	{
		DatabaseSchema db = new DatabaseSchema();
		String query = "SELECT * FROM " + db.table("game_image") +
			" WHERE id=? ";
		List<GameImage> l = db.query( query, new Object[] { new Integer(id) }, new GameImageRowMapper() );
		return ( l.size() > 0 ) ? l.get( 0 ) : null;
	}
}
