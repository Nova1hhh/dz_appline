package ru.appnile;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashMap;
import java.util.Map;

@RestController
public class Controller {
    Map<Integer, String> compass = new HashMap<>();

    public int[] parser (Map<String, String> side, String temp) {
        String str = side.get(temp);
        String[] str1 = str.split("-");
        int num1 = Integer.parseInt(str1[0]);
        int num2 = Integer.parseInt(str1[1]);
        return new int[] {num1, num2};
    }

    @PostMapping(value = "/postCompass", consumes = "application/json")
    public Map<Integer, String> createCompass(@RequestBody Map<String, String> side) {
        int[] n = parser(side, "NORTH");
        for (int i = 0; i <= n[1]; i++) {
            compass.put(i, "NORTH");
        }
        for (int i = n[0]; i <= 359; i++) {
            compass.put(i, "NORTH");
        }

        int[] ne = parser(side, "NORTHEAST");
        for (int i = ne[0]; i <= ne[1]; i++) {
            compass.put(i, "NORTHEAST");
        }

        int[] e = parser(side, "EAST");
        for (int i = e[0]; i <= e[1]; i++) {
            compass.put(i, "EAST");
        }

        int[] se = parser(side, "SOUTHEAST");
        for (int i = se[0]; i <= se[1]; i++) {
            compass.put(i, "SOUTHEAST");
        }

        int[] s = parser(side, "SOUTH");
        for (int i = s[0]; i <= s[1]; i++) {
            compass.put(i, "SOUTH");
        }

        int[] sw = parser(side, "SOUTHWEST");
        for (int i = sw[0]; i <= sw[1]; i++) {
            compass.put(i, "SOUTHWEST");
        }

        int[] w = parser(side, "WEST");
        for (int i = w[0]; i <= w[1]; i++) {
            compass.put(i, "WEST");
        }

        int[] nw = parser(side, "NORTHWEST");
        for (int i = nw[0]; i <= nw[1]; i++) {
            compass.put(i, "NORTHWEST");
        }
        return compass;
    }

    @GetMapping(value = "/getSide", consumes = "application/json", produces = "application/json")
    public Map<String, String> getSide(@RequestBody Map<String, Integer> rq){
        int degree = rq.get("DEGREE");
        Map<String,String> ans = new HashMap<>();
        ans.put("SIDE", compass.get(degree));
        return ans;
    }
}

//_____________пример запроса________________________________________________

//    {
//            "NORTH":"338-22",
//            "NORTHEAST":"23-67",
//            "EAST":"68-112",
//            "SOUTHEAST":"113-157",
//            "SOUTH":"158-202",
//            "SOUTHWEST":"203-247",
//            "WEST":"248-292",
//            "NORTHWEST":"293-337"
//    }

//    {
//            "DEGREE": 200
//    }