<%@ include file="/WEB-INF/jsp/include.jsp" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/2000/REC-xhtml1-20000126/DTD/xhtml1-transitional.dtd">
<html>
<head>
	<title>GameN'Watch - Find Users</title>
	<link rel="stylesheet" href="style.css" type="text/css" />
</head>

<body>
<h1 align="center">GameN'Watch</h1>

<div id="leftcontent">
	<p><b>GameN'Watch</b></p>
	<ul>
		<li><a href="index.html">Home</a></li>
	</ul>
	<p><b>Games</b></p>
	<ul>
		<li><a href="#">New Releases</a></li>
		<li><a href="#">Upcoming</a></li>
		<li><a href="#">Top Games</a></li>
		<li><a href="searchgames.html">Find Games</a></li>
	</ul>
	<form action="qresults.html">
		<p><b>Search:</b><br>
		<input type="text" name="search" size="15"></p>
		<input type="submit" value="Search">
	</form>
	<p><b>Users</b></p>
	<ul>
		<li><a href="#">Login</a></li>
		<li><a href="#">Sign Up</a></li>
		<li><a href="searchusers.html">Find Users</a></li>
	</ul>
</div>

<div id="rightcontent">
	<form method="post">
		<spring:bind path="user.userName">
		UserName: <input type="text" name="userName" value="<c:out value="${status.value}"/>">&nbsp;&nbsp;<span class="error"><c:out value="${status.errorMessage}"/></span><br>
		</spring:bind>
		<spring:hasBindErrors name="user">
    		<b>Please fix all errors!</b>
  		</spring:hasBindErrors>
		<br><br>
		<input type="submit" value="Search">
	</form>
</div>

<br>
</body></html>
