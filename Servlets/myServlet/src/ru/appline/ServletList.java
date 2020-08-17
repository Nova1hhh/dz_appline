package ru.appline;


import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;
import ru.appline.logic.Model;
import ru.appline.logic.User;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Map;

@WebServlet(urlPatterns = "/get")
public class ServletList extends HttpServlet {

    Model model = Model.getInstance();

    Gson gson = new GsonBuilder().setPrettyPrinting().create();

//    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
//        response.setContentType("text/html;charset=utf-8");
//        PrintWriter pw = response.getWriter();
//
//        int id = Integer.parseInt(request.getParameter("id"));
//
//        if (id == 0) {
//            pw.print("<html>" +
//                    "<h3>Доступные пользователи</h3><br/>" +
//                    "ID пользователя: " +
//                    "<ul>");
//
//            for (Map.Entry<Integer, User> entry : model.getFrom_List().entrySet()) {
//                pw.print("<li>" + entry.getKey() + "</li>" +
//                        "<ul>" +
//                        "<li>Имя: " + entry.getValue().getName() + "</li>" +
//                        "<li>Фамилия: " + entry.getValue().getSurname() + "</li>" +
//                        "<li>Зарплата: " + entry.getValue().getSalary() + "</li>" +
//                        "</ul>");
//            }
//
//            pw.print("</ul>" +
//                    "<a href=\"index.jsp\">Домой</a>" +
//                    "</html>");
//        } else if (id > 0) {
//            if (id > model.getFrom_List().size()) {
//                pw.print("<html>" +
//                        "<h3>Такого пользователя нет =( </h3>" +
//                        "<a href=\"index.jsp\">Домой</a>" +
//                        "</html>");
//            } else {
//                pw.print("<html>" +
//                        "<h3>Запрошенный пользователь:</h3><br/>" +
//                        "Имя: " + model.getFrom_List().get(id).getName() + "<br/>" +
//                        "Фамилия: " + model.getFrom_List().get(id).getSurname() + "<br/>" +
//                        "Зарплата: " + model.getFrom_List().get(id).getSalary() + "<br/>" +
//                        "<a href=\"index.jsp\">Домой</a>" +
//                        "</html>");
//            }
//        } else {
//            pw.print("<html>" +
//                    "<h3>ID должен быть больше нуля</h3>" +
//                    "<a href=\"index.jsp\">Домой</a>" +
//                    "</html>");
//        }
//    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        StringBuffer j_list = new StringBuffer();
        String line;
        try {
            BufferedReader reader = request.getReader();
            while ((line = reader.readLine()) != null) {
                j_list.append(line);
            }
        } catch (Exception e) {
            System.out.println("error");
        }

        JsonObject j_obj = gson.fromJson(String.valueOf(j_list), JsonObject.class);
        //int id = Integer.parseInt(request.getParameter("id"));
        //request.setCharacterEncoding("UTF-8");
        PrintWriter pw = response.getWriter();
        response.setContentType("application/json;charset=utf-8");

        int id = j_obj.get("id").getAsInt();

        if (id == 0) {
            pw.print(gson.toJson(model.getFrom_List()));
        } else if (id > 0) {
            pw.print(gson.toJson(model.getFrom_List().get(id)));
        } else {
            pw.print(gson.toJson("ID must be over then 0!"));
        }

    }

}
