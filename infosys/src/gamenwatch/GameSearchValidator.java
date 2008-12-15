/**
 * GameSearchValidator.java
 *
 * Validator for the game search form
 */

import java.io.Serializable;
import org.springframework.validation.Validator;
import org.springframework.validation.Errors;

import gamenwatch.*;

public class GameSearchValidator implements Validator {
	
	public boolean supports(Class clazz) {
       return Game.class.isAssignableFrom(clazz);
    }

	public void validate(Object obj, Errors errors) {

	}
}
