/**
 * DatabaseSchema.java
 * Extremely simple database schema management.
 * Maintains the appropriate database schema information, with automated
 * updates to the schema based on a schema "version" configuration.  By adding
 * incremental schema changes as new elements to the changes[] array, an 
 * existing database will be automatically upgraded appropriately.
 *
 * @author John Reese
 */
package gamenwatch;

import java.sql.ResultSet;
import java.util.ResourceBundle;
import java.util.regex.Pattern;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.commons.dbcp.BasicDataSource;

import org.springframework.jdbc.core.*;
import org.springframework.jdbc.support.rowset.*;

public class DatabaseSchema extends JdbcTemplate
{
	public static String[] schema() {
		return new String[] { "",
		"CREATE TABLE " + table("developer") + " ( id INT AUTO_INCREMENT NOT NULL, name VARCHAR(100), email VARCHAR(200), description TEXT, PRIMARY KEY ( id, name ) )",
		"CREATE TABLE " + table("publisher") + " ( id INT AUTO_INCREMENT NOT NULL, name VARCHAR(100), email VARCHAR(200), description TEXT, PRIMARY KEY ( id, name ) )",
		"CREATE TABLE " + table("platform") + " ( id INT AUTO_INCREMENT NOT NULL, name VARCHAR(100), description TEXT, PRIMARY KEY ( id, name ) )",
		"CREATE TABLE " + table("genre") + " ( id INT AUTO_INCREMENT NOT NULL, name VARCHAR(100), description TEXT, PRIMARY KEY ( id, name ) )",
		"CREATE TABLE " + table("game") + " ( id INT AUTO_INCREMENT NOT NULL, name VARCHAR(50) NOT NULL, developer_id INT, publisher_id INT, description TEXT, status VARCHAR(50), launch DATE, sales INT, profit DOUBLE, img VARCHAR(50), PRIMARY KEY ( id, name ), INDEX ( status, launch ), INDEX ( developer_id, publisher_id ) )",
		"CREATE TABLE " + table("game_genre") + " ( game_id INT NOT NULL, genre_id INT NOT NULL, PRIMARY KEY ( game_id, genre_id ) )",
		"CREATE TABLE " + table("game_platform") + " ( game_id INT NOT NULL, platform_id INT NOT NULL, PRIMARY KEY ( game_id, platform_id ) )",
		"CREATE TABLE " + table("user") + " ( id INT AUTO_INCREMENT NOT NULL, username VARCHAR(20) NOT NULL, email VARCHAR(200) NOT NULL, fname VARCHAR(50), lname VARCHAR(50), address TEXT, PRIMARY KEY ( id, username, email ) )",
		"CREATE TABLE " + table("user_friends") + " ( user1 INT NOT NULL, user2 INT NOT NULL, status INT NOT NULL DEFAULT 0, PRIMARY KEY ( user1, user2 ) )",
		"ALTER TABLE " + table("game") + " ADD CONSTRAINT fk_game_developer FOREIGN KEY ( developer_id ) REFERENCES " + table("developer") + " ( id )",
		"ALTER TABLE " + table("game") + " ADD CONSTRAINT fk_game_publisher FOREIGN KEY ( publisher_id ) REFERENCES " + table("publisher") + " ( id )",
		"ALTER TABLE " + table("game_genre") + " ADD CONSTRAINT fk_game_genre_game FOREIGN KEY ( game_id ) REFERENCES " + table("game") + " ( id )",
		"ALTER TABLE " + table("game_genre") + " ADD CONSTRAINT fk_game_genre_genre FOREIGN KEY ( genre_id ) REFERENCES " + table("genre") + " ( id )",
		"ALTER TABLE " + table("game_platform") + " ADD CONSTRAINT fk_game_platform_game FOREIGN KEY ( game_id ) REFERENCES " + table("game") + " ( id )",
		"ALTER TABLE " + table("game_platform") + " ADD CONSTRAINT fk_game_platform_platform FOREIGN KEY ( platform_id ) REFERENCES " + table("platform") + " ( id )",
		"ALTER TABLE " + table("user_friends") + " ADD CONSTRAINT fk_user_friends_user1 FOREIGN KEY ( user1 ) REFERENCES " + table("user") + " ( id )",
		"ALTER TABLE " + table("user_friends") + " ADD CONSTRAINT fk_user_friends_user2 FOREIGN KEY ( user2 ) REFERENCES " + table("user") + " ( id )",
		"CREATE TABLE " + table("game_similar") + " ( game1 INT NOT NULL, game2 INT NOT NULL, PRIMARY KEY ( game1, game2 ) )",
		"ALTER TABLE " + table("game_similar") + " ADD CONSTRAINT fk_game_similar_game1 FOREIGN KEY ( game1 ) REFERENCES " + table("game") + " ( id )",
		"ALTER TABLE " + table("game_similar") + " ADD CONSTRAINT fk_game_similar_game2 FOREIGN KEY ( game2 ) REFERENCES " + table("game") + " ( id )",
		"CREATE TABLE " + table("game_image") + " ( id INT AUTO_INCREMENT NOT NULL, game_id INT NOT NULL, type INT NOT NULL DEFAULT 0, image BLOB NOT NULL, PRIMARY KEY ( id, game_id ), INDEX ( type ) )",
		"ALTER TABLE " + table("game_image") + " ADD CONSTRAINT fk_game_image_game FOREIGN KEY ( game_id ) REFERENCES " + table("game") + " ( id )",
		"CREATE TABLE " + table("user_game") + " ( user_id INT NOT NULL, game_id INT NOT NULL, type INT NOT NULL DEFAULT 0, PRIMARY KEY ( user_id, game_id, type ) )",
		"ALTER TABLE " + table("user_game") + " ADD CONSTRAINT fk_user_game_user FOREIGN KEY ( user_id ) REFERENCES " + table("user") + " ( id )",
		"ALTER TABLE " + table("user_game") + " ADD CONSTRAINT fk_user_game_game FOREIGN KEY ( game_id ) REFERENCES " + table("game") + " ( id )",
		"" //insert new schema changes above this line
		};
	}

	public static BasicDataSource dataSource = null;
	public static Log log = null;

	public static String prefix;
	public static String table( String name )  { return prefix + name; }

	public DatabaseSchema() 
	{ 
		this( null ); 
	}

	public DatabaseSchema( Log log )
	{
		super( initDataSource( log ) );
		this.log = log;
	}

	private static BasicDataSource initDataSource( Log log )
	{
		if ( log != null ) {
			DatabaseSchema.log = log;
		}
		if ( dataSource == null ) {
			ResourceBundle rb = ResourceBundle.getBundle( "datasource" );
			String driver = rb.getString( "driver" );
			String url = rb.getString( "url" );
			String username = rb.getString( "username" );
			String password = rb.getString( "password" );

			prefix = rb.getString( "prefix" );

			if ( log != null ) { log.info( "Driver: '" + driver + "' - URL: '" + url + "'" ); }
			dataSource = new BasicDataSource();
			dataSource.setDriverClassName(driver);
			dataSource.setUrl(url);
			dataSource.setUsername(username);
			dataSource.setPassword(password);
		
			checkSchema();
		}
		return dataSource;
	}

	private static void checkSchema()
	{
		JdbcTemplate db = new JdbcTemplate( dataSource );
		String query = "";

		String configTable = table( "config" );
		boolean tableExists = false;

		query = "SHOW TABLES LIKE '" + configTable + "'";
		SqlRowSet result = db.queryForRowSet( query );

		while ( result.next() ) {
			if ( result.getString( 1 ).equals( configTable ) ) {
				tableExists = true;
			}
		}

		if ( !tableExists ) {
			if ( log != null ) { log.info( "Creating schema configuration table..." ); }

			query = "CREATE TABLE " + configTable + " ( name VARCHAR(50) NOT NULL PRIMARY KEY, value VARCHAR(200) ) ";
			db.execute( query );

			query = "INSERT INTO " + configTable + " ( name, value ) VALUES ( 'schema', '0' ) ";
			db.execute( query );
		}

		query = "SELECT value FROM " + configTable + " WHERE name='schema'";
		int dbVersion = db.queryForInt( query );

		String[] changes = schema();
		int schemaVersion = changes.length - 2;

		if ( log != null ) { log.info( "Current schema version: " + schemaVersion );
				log.info( "Current database version: " + dbVersion ); }

		if ( dbVersion >= schemaVersion ) {
			return;
		}

		for ( int i = dbVersion + 1; i <= schemaVersion; i++ ) {
			query = changes[i];
			db.execute( query );

			query = "UPDATE " + configTable + " SET value='" + i + "' WHERE name='schema'";
			db.execute( query );

			if ( log != null ) { log.info( "Database updated to version " + i + "." ); }
		}
	}
}
