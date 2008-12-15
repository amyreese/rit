<%@ include file="/WEB-INF/jsp/include.jsp" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/2000/REC-xhtml1-20000126/DTD/xhtml1-transitional.dtd">
<html>
<head>
	<title>Game - <c:out value="${model.game.name}"/></title>
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
	<div class="game-left">
		<img src="images/<c:out value="${model.game.img}"/>"><br><br>
		<b>System:</b> 
			<c:forEach items="${model.game.platforms}" var="platform" varStatus="status">
				<c:out value="${platform.systemName}"/> 
			</c:forEach>
		<br>
		<b>Genre:</b> 
			<c:forEach items="${model.game.genres}" var="genre">
				<c:out value="${genre.name}"/> 
			</c:forEach>
		<br>
		<b>Status:</b> <c:out value="${model.game.status}"/><br>
		<b>Release Date:</b> <fmt:formatDate value="${model.game.releaseDate}" type="date" dateStyle="MEDIUM"/><br>
		<b>Developer:</b> <c:out value="${model.game.developer.name}"/><br>
		<b>Publisher:</b> <c:out value="${model.game.publisher.name}"/><br><br>
		<a href="#"><b>Track this game</b></a><br>
		<a href="#"><b>View similar games</b></a>
	</div>
	<div class="game-right">
		<div class="border-light">
			<p class="game-title"><c:out value="${model.game.name}"/></p>
			<p><c:out value="${model.game.description}"/></p>
		</div><br>
		<div class="border-light">
			<p><b>Other users tracking this game:</b></p>
			<ul>
				<c:forEach items="${model.users}" var="user">
					<c:url value="user.html" var="url">
						<c:param name="id" value="${user.id}"/>
					</c:url>
					<li><a href="<c:out value="${url}"/>"><c:out value="${user.userName}"/></a></li>
				</c:forEach>
			</ul>
		</div>
	</div>
	<div class="spacer">
		&nbsp;
	</div>
</div>

<br>
</body></html>
