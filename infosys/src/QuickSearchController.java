/**
 * QuickSearchController.java
 *
 * Controller for the quick search results page
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

public class QuickSearchController implements Controller
{
	/** Logger */
	protected final Log logger = LogFactory.getLog(getClass());

	public ModelAndView handleRequest( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException
	{
		new DatabaseSchema( logger );

		// Get the name of the game to search for
		String name = request.getParameter("search");

		GameService service = new GameService();
		List<Game> results = service.searchByName(name);
				
		return new ModelAndView( "results", "results", results );
	}
}

