/**
* UserService.java
*
* Service class which provides various functionality relating to users
*/

import gamenwatch.*;
import java.util.*;

public class UserService {

	public UserService(){ }

	public List<User> searchByName( String uName ) {
		
		List<User> users = UserDao.find(uName);
		
		return users;
	}

	public User getUser( int id ) {
		User u = UserDao.load(id);

		return u;
	}
}

