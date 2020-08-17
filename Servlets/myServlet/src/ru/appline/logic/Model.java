package ru.appline.logic;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

public class Model implements Serializable {
    private static final Model instance = new Model();

    private final Map<Integer, User> model;

    public static Model getInstance() {
        return instance;
    }

    private Model() {
        model = new HashMap<>();

        model.put(1, new User("Bulankin", "Nikolay", 1111));
        model.put(2, new User("Nevelniy", "Alex", 2222));
        model.put(3, new User("Vorobjeva", "Lili", 3333));
    }

    public void add(User user, int id){
        model.put(id, user);
    }

    public Map<Integer, User> getFrom_List() {
        return model;
    }

    public Map<Integer, User> delete() {
        model.clear();
        return model;
    }

    public Map<Integer, User> delete(int id) {
        model.remove(id);
        return model;
    }

    public Map<Integer, User> replace(int id, User user) {
        model.replace(id, user);
        return model;
    }


}
