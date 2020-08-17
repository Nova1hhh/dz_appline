package ru.appline;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;
import ru.appline.logic.Model;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(urlPatterns = "/del")
public class ServletDelete extends HttpServlet {
    Model model = Model.getInstance();

    Gson gson = new GsonBuilder().setPrettyPrinting().create();

    protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws IOException {
        StringBuffer j_del = new StringBuffer();
        String line;
        try {
            BufferedReader reader = request.getReader();
            while ((line = reader.readLine()) != null) {
                j_del.append(line);
            }
        } catch (Exception e) {
            System.out.println("Error");
        }
        JsonObject j_obj = gson.fromJson(String.valueOf(j_del), JsonObject.class);

        PrintWriter pw = response.getWriter();
        response.setContentType("application/json;charset=utf-8");

        int id = j_obj.get("id").getAsInt();

        if (id == 0) {
            pw.print(gson.toJson(model.delete()));
        } else if (id > 0) {
            pw.print(gson.toJson(model.delete(id)));
        } else {
            pw.print(gson.toJson("ID must be over then 0"));
        }

    }
}
