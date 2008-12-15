<%@ include file="/WEB-INF/jsp/include.jsp" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/2000/REC-xhtml1-20000126/DTD/xhtml1-transitional.dtd">
<html>
<head>
	<title>GameN'Watch - Search Results</title>
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
	<h2 align="center">Search Results</h2>
	
	<c:forEach items="${results}" var="user">
		<c:url value="user.html" var="url">
			<c:param name="id" value="${user.id}"/>
		</c:url>

		<a href="<c:out value="${url}"/>"><c:out value="${user.userName}"/></a><br>
	</c:forEach>
</div>

<br>
</body></html>

