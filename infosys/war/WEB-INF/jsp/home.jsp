<%@ include file="/WEB-INF/jsp/include.jsp" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/2000/REC-xhtml1-20000126/DTD/xhtml1-transitional.dtd">
<html>
<head>
	<title>GameN'Watch - Home Page</title>
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
	<div class="border-light">
		<p>
			Welcome to GameN'Watch, the site that lets you easily track new and upcoming games.  Start by signing up for an account then track some 			games your interested in.  You'll be able to view all sorts of info about the games and stay updated on their status.  GameN'Watch is a 			great way to find new games you didn't know about,  look at the upcoming games or top games sections and you may find something new and 			exciting.
		</p>
	</div><br><br>
	<div class="infobox">
		<div class="infohead">Top Tracked Games</div>
		<ol>
			<!-- Loop through the top tracked games returned from the controller -->
			<c:forEach items="${model.tracked}" var="game">
				<c:url value="game.html" var="url">
					<c:param name="id" value="${game.id}"/>
				</c:url>
				
				<li><a href="<c:out value="${url}"/>"><c:out value="${game.name}"/></a></li>
			</c:forEach>
		</ol>
	</div>

	<div class="infobox">
		<div class="infohead">Upcoming Games</div>
		<ul>
			<!-- Loop through the upcoming games returned from the controller -->
			<c:forEach items="${model.upcoming}" var="game">
				<c:url value="game.html" var="url">
					<c:param name="id" value="${game.id}"/>
				</c:url>
				<li><a href="<c:out value="${url}"/>"><c:out value="${game.name}"/></a> - <fmt:formatDate value="${game.releaseDate}" type="date" dateStyle="MEDIUM"/></li>
			</c:forEach>
		</ul>
	</div>

	<div class="infobox">
		<div class="infohead">Recently Updated</div>
		<ul>
			<!-- Loop through the updated games returned from the controller -->
			<c:forEach items="${model.updated}" var="game">
				<c:url value="game.html" var="url">
					<c:param name="id" value="${game.id}"/>
				</c:url>
				<li><a href="<c:out value="${url}"/>"><c:out value="${game.name}"/></a></li>
			</c:forEach>
		</ul>
	</div>

	<div class="spacer">
		&nbsp;
	</div>
</div>

<br>
</body></html>

