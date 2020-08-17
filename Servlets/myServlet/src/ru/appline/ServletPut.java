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

@WebServlet(urlPatterns = "/put")
public class ServletPut extends HttpServlet {
    Model model = Model.getInstance();

    Gson gson = new GsonBuilder().setPrettyPrinting().create();

    protected void doPut(HttpServletRequest request, HttpServletResponse response) throws IOException {
        StringBuffer j_put = new StringBuffer();
        String line;
        try {
            BufferedReader reader = request.getReader();
            while ((line = reader.readLine()) != null) {
                j_put.append(line);
            }
        } catch (Exception e) {
            System.out.println("Error");
        }

        JsonObject j_obj = gson.fromJson(String.valueOf(j_put), JsonObject.class);
        request.setCharacterEncoding("UTF-8");

        PrintWriter pw = response.getWriter();
        response.setContentType("application/json;charset=utf-8");

        String name = j_obj.get("name").getAsString();
        String surname = j_obj.get("surname").getAsString();
        double salary = j_obj.get("salary").getAsDouble();

        User user = new User(name, surname, salary);
        int id = j_obj.get("id").getAsInt();

        if (id > 0) {
            pw.print(gson.toJson(model.replace(id, user)));
        } else {
            pw.print(gson.toJson("error: invalid ID!"));
        }

    }
}
