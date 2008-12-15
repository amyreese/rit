/**
 * GamePageController.java
 *
 * Controller for the game details page
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

public class GamePageController implements Controller
{
	/** Logger */
	protected final Log logger = LogFactory.getLog(getClass());

	/**
	 * Barebones MVC.
	 */
	public ModelAndView handleRequest( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException
	{
		new DatabaseSchema( logger );

		// Get the id of the game
		int id = Integer.parseInt(request.getParameter("id"));

		GameService service = new GameService();
		Game game = service.getGame(id);
		List<User> users = service.getUsers(id);

		Map myModel = new HashMap();
        myModel.put("game", game);
		myModel.put("users", users);
		return new ModelAndView( "game", "model", myModel );
	}
}
