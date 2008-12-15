/**
 * HomeController.java
 *
 * Controller for the home page of the system
 */

import org.springframework.web.servlet.mvc.Controller;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.io.IOException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import gamenwatch.*;
import java.util.*;

public class HomeController implements Controller
{
	/** Logger */
	protected final Log logger = LogFactory.getLog(getClass());

	/**
	 * Barebones MVC.
	 */
	public ModelAndView handleRequest( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException
	{
		new DatabaseSchema( logger );

		/*
		*  Need to return top ten tracked games, ten upcoming games and ten recently updated games.
		*  These should come from the game service.
		*/

		GameService service = new GameService();
		List<Game> gamesTracked = service.getTopTrackedGames( 10 );
		List<Game> gamesUpcoming = service.getUpcomingGames( 10 );
		List<Game> gamesUpdated = service.getUpdatedGames( 10 );
		Map<String,List<Game>> myModel = new HashMap<String,List<Game>>();
        myModel.put("tracked", gamesTracked);
		myModel.put("upcoming", gamesUpcoming);
		myModel.put("updated", gamesUpdated);
				
		return new ModelAndView( "home", "model", myModel );
	}
}

