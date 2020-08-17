package calc;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

@WebServlet(urlPatterns = "/get")
public class Servlet extends HttpServlet {
    Gson gson = new GsonBuilder().setPrettyPrinting().create();
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuffer rq = new StringBuffer();
        String line;
        try {
            BufferedReader reader = request.getReader();
            while ((line = reader.readLine()) != null) {
                rq.append(line);
            }
        } catch (Exception e) {
            System.out.println("Error");
        }

        JsonObject j_obj = gson.fromJson(String.valueOf(rq), JsonObject.class);

        request.setCharacterEncoding("UTF-8");

        double a = j_obj.get("a").getAsDouble();
        double b = j_obj.get("b").getAsDouble();
        String op = j_obj.get("math").getAsString();
        double res;

        response.setContentType("application/json;charset=utf-8");
        PrintWriter pw = response.getWriter();

        Map<String, Double> result = new HashMap<>();

        if (op.equals("+")) {
            res = a + b;
            result.put("result", res);
            pw.print(gson.toJson(result));
        } else if (op.equals("-")) {
            res = a - b;
            result.put("result", res);
            pw.print(gson.toJson(result));
        } else if (op.equals("*")) {
            res = a * b;
            result.put("result", res);
            pw.print(gson.toJson(result));
        } else if (op.equals("^")){
            res = Math.pow(a,b);
            result.put("result", res);
            pw.print(gson.toJson(result));
        } else if (op.equals("/")){
            if (b == 0) {
                pw.print(gson.toJson("division by zero"));
            } else {
                res = a / b;
                result.put("result", res);
                pw.print(gson.toJson(result));
            }
        }
    }

}
