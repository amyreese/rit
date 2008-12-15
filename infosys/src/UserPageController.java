/**
 * UserPageController.java
 *
 * Controller for a users profile page
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

public class UserPageController implements Controller
{
	/** Logger */
	protected final Log logger = LogFactory.getLog(getClass());

	/**
	 * Barebones MVC.
	 */
	public ModelAndView handleRequest( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException
	{
		new DatabaseSchema( logger );

		// Get the id of the user
		int id = Integer.parseInt(request.getParameter("id"));

		UserService service = new UserService();
		User user = service.getUser(id);
		List<Game> tracked = user.gamesTracked();
		List<Game> owned = user.gamesOwned();
		List<User> friends = user.friends();

		Map myModel = new HashMap();
        myModel.put("user", user);
		myModel.put("tracked", tracked);
		myModel.put("owned", owned);
		myModel.put("friends", friends);
		return new ModelAndView( "user", "model", myModel );
	}
}
