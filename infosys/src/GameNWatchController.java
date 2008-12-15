/**
 * GameNWatchController.java
 * Primary servlet for the Game N Watch web application.
 *
 * @author John Reese
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

public class GameNWatchController implements Controller
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
		Publisher p = PublisherDao.load( 1 );

		String val = p.getName();
		p.setName( val + " X" );
		PublisherDao.save(p);

		val = p.getName();
		*/
		String val = "Random Value";
		return new ModelAndView( "home", "value", val );
	}
}

