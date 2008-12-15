import org.springframework.web.servlet.mvc.Controller;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.io.IOException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import gamenwatch.*;
import java.sql.Date;
import java.util.*;

public class FillDatabaseController implements Controller
{
	/** Logger */
	protected final Log logger = LogFactory.getLog(getClass());

	/**
	 * Barebones MVC.
	 */
	public ModelAndView handleRequest( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException
	{
		new DatabaseSchema( logger );
		Calendar cal = new GregorianCalendar();

		Developer valve = new Developer("Valve Software");
		DeveloperDao.save( valve );

		Developer crytek = new Developer("Crytek");
		DeveloperDao.save( crytek );

		Developer gpg = new Developer("Gas Powered Games");
		DeveloperDao.save( gpg );

		Publisher valvepub = new Publisher("Valve Software");
		PublisherDao.save( valvepub );

		Publisher ea = new Publisher("Electronic Arts");
		PublisherDao.save( ea );

		Publisher thq = new Publisher("THQ");
		PublisherDao.save( thq );

		Genre fps = new Genre("First Person Shooter");
		GenreDao.save( fps );

		Genre rts = new Genre("Real Time Strategy");
		GenreDao.save( rts );

		Platform pc = new Platform("PC");
		PlatformDao.save( pc );

		Platform ps3 = new Platform("PS3");
		PlatformDao.save( ps3 );

		Platform xbox360 = new Platform("XBox 360");
		PlatformDao.save( xbox360 );

		List<Genre> genres = new ArrayList<Genre>();
		List<Platform> platforms = new ArrayList<Platform>();

		Game crysis = new Game("Crysis");
			crysis.setDescription("Crysis is an upcoming science fiction first-person shooter computer game, that is being developed by Crytek, and published by Electronic Arts. Crysis is based in a fictional future where an alien race has invaded Earth. The single player campaign has the player assume the role of United States Delta Force operative Jake Dunn. Dunn is armed with various futuristic weapons and equipment, most notably a 'Nano Muscle Suit'. According to Crytek senior game designer Bernd Diemer, the suit was inspired by the United States' Future Warrior 2020 program. In Crysis, the player fights both North Korean and extraterrestrial enemies, in four different locations: a tropical island jungle; an American aircraft carrier; inside an 'Ice Sphere', which will consist of the same jungle, but frozen; and the alien ship itself, some parts of which will be zero-gravity. Crysis will utilize Microsoft's new API, Direct3D 10 (DirectX 10) for graphics rendering, and will include the same editor that was used by Crytek to create the game.");
			crysis.setStatus("Not Yet Released");
			cal.set(2007, 10, 15);
			crysis.setReleaseDate(new Date(cal.getTimeInMillis()));
			crysis.setDeveloper(crytek);
			crysis.setPublisher(ea);
			genres.add(fps);
			crysis.setGenres(genres);
			platforms.add(pc);
			crysis.setPlatforms(platforms);
			crysis.setImg("CrysisBox.jpg");
		GameDao.save( crysis );

		Game hl2 = new Game("Half-Life 2");
			hl2.setDescription("A hallmark shooter set in the post-modern future where Earth has been invaded and conquered by the alien Combine Overwatch.");
			hl2.setStatus("Released");
			cal.set(2004, 11, 16);
			hl2.setReleaseDate(new Date(cal.getTimeInMillis()));
			hl2.setDeveloper(valve);
			hl2.setPublisher(valvepub);
			hl2.setGenres(genres);
			platforms.add(ps3);
			platforms.add(xbox360);
			hl2.setPlatforms(platforms);
			hl2.setImg("HL2Box.jpg");
		GameDao.save( hl2 );

		Game supcom = new Game("Supreme Commander");
			supcom.setDescription("Spiritual successor to the 1997 hit strategy game Total Annihilation, Supreme Commander takes battlefield tactics to a new order of magnitude, with the ability to zoom in to see and manage individual units, or zoom back to view the entire battelfield at once and command your troops like a true General would.");
			supcom.setStatus("Released");
			cal.set(2007, 2, 20);
			supcom.setReleaseDate(new Date(cal.getTimeInMillis()));
			supcom.setDeveloper(gpg);
			supcom.setPublisher(thq);
			genres.clear();
			genres.add(rts);
			supcom.setGenres(genres);
			platforms.clear();
			platforms.add(pc);
			supcom.setPlatforms(platforms);
			supcom.setImg("SupComBox.jpg");
		GameDao.save( supcom );

		User john = new User("jreese");
			john.setFirstName("John");
			john.setLastName("Reese");
			john.setEmail("jmr8223@rit.edu");
		UserDao.save( john );

		User andrew = new User("astorrow");
			andrew.setFirstName("Andrew");
			andrew.setLastName("Storrow");
			andrew.setEmail("acs3267@rit.edu");
		UserDao.save( andrew );

		User ben = new User("broux");
			ben.setFirstName("Ben");
			ben.setLastName("Roux");
			ben.setEmail("bsr1540@rit.edu");
		UserDao.save( ben );


		return new ModelAndView( "fill", "model", null );
	}
}

