/**
 * GameSearchController.java
 *
 * Controller for searching for games
 */

import org.springframework.web.servlet.mvc.*;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.view.RedirectView;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.io.IOException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import gamenwatch.*;
import java.util.*;

public class GameSearchController extends SimpleFormController
{
	/** Logger */
	protected final Log logger = LogFactory.getLog(getClass());

	public ModelAndView onSubmit(Object command) throws ServletException {
		GameService service = new GameService();
		String name = ((Game) command).getName();
		List<Game> results = service.searchByName(name);

		return new ModelAndView( "gameresults", "results", results );
	}
}
