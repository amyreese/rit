<%@ include file="/WEB-INF/jsp/include.jsp" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/2000/REC-xhtml1-20000126/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta http-equiv="content-type" content="text/html; charset=iso-8859-1">
	<title>User - <c:out value="${model.user.userName}"/></title>
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
		<img src="images/no_avatar.png"><br><br>
		<b>Status:</b> <a href="#">Offline</a><br><br>
		<a href="#"><b>Add as friend</b></a><br>
		<a href="#"><b>Compare games</b></a>
	</div>
	<div class="game-right">
		<div class="border-light">
			<p class="game-title"><c:out value="${model.user.userName}"/></p>
		</div><br>
		<div class="border-light">
			<p><b>Games tracked</b></p>
			<ul>
				<c:forEach items="${model.tracked}" var="game">
					<c:url value="game.html" var="url">
						<c:param name="id" value="${game.id}"/>
					</c:url>
					<li><a href="<c:out value="${url}"/>"><c:out value="${game.name}"/></a></li>
				</c:forEach>
			</ul>
		</div><br>
		<div class="border-light">
			<p><b>Games Owned</b></p>
			<ul>
				<c:forEach items="${model.owned}" var="game">
					<c:url value="game.html" var="url">
						<c:param name="id" value="${game.id}"/>
					</c:url>
					<li><a href="<c:out value="${url}"/>"><c:out value="${game.name}"/></a></li>
				</c:forEach>
			</ul>
		</div><br>
		<div class="border-light">
			<p><b>Friends</b></p>
			<ul>
				<c:forEach items="${model.friends}" var="user">
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


</body></html>
