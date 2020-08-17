<%@ page import="ru.appline.logic.Model"%>
<%--
  Created by IntelliJ IDEA.
  User: Николай
  Date: 16.08.2020
  Time: 5:18
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
  <head>
    <title>Title</title>
  </head>
  <body>
  <h1>Домашняя страница по работе с пользователями</h1>
  Введите ID пользователя (0 - для вывода всего списка пользователей)
  <br/>
  Доступно: <%
  Model model = Model.getInstance();
  out.print(model.getFrom_List().size());
  %>
  <form method="get" action="get">
    <label>ID:
      <input type="text" name="id"><br/>
    </label>
    <button type="submit">Поиск</button>
  </form>

  <a href="addUser.html">Создать нового пользователя</a>
  </body>
</html>
