package ru.appline.controller;

import org.springframework.web.bind.annotation.*;
import ru.appline.logic.Pet;
import ru.appline.logic.PetModel;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

@RestController
public class Controller {
    private static final PetModel petModel = PetModel.getInstance();
    private static final AtomicInteger newId = new AtomicInteger(1);

    @PostMapping(value = "/createPet", consumes = "application/json")
    public Map<String, String> createPet(@RequestBody Pet pet) {
        petModel.add(pet, newId.getAndIncrement());
        Map<String , String> rsp = new HashMap<String, String>();
        rsp.put("response", "gz! You created 1st pet");
        if (newId.get() > 2) {
            rsp.put("response", "Created new pet");
        }
        return rsp;
    }

    @GetMapping(value = "/getAll", produces = "application/json")
    public Map<Integer, Pet> getAll() {
        return petModel.getAll();
    }


    @GetMapping(value = "/getPet", consumes = "application/json", produces = "application/json")
    public Pet getPet(@RequestBody Map<String, Integer> id) {
        return petModel.getFromList(id.get("id"));
    }

    @DeleteMapping(value = "/deletePet", consumes = "application/json", produces = "application/json")
    public Map<Integer, Pet> delPet(@RequestBody Map<String, Integer> id) {
        petModel.delPet(id.get("id"));
        return petModel.getAll();
    }

    @PutMapping(value = "/putPet", consumes = "application/json", produces = "application/json")
    public Map<Integer, Pet> updPet(@RequestBody Map <Integer, Pet> pet) {
        // ща тут будет жесткий костыль xD
        // Вид запроса, с которым это работает
//        {
//            "1":
//            {
//                "name":"zelda",
//                "type":"dog",
//                "age":2
//            }
//        }

        Set<Integer> set = pet.keySet();
        Integer[] array = set.toArray(new Integer[0]);
        int id = array[0];
        Pet new_pet = pet.get(id);
        petModel.updatePet(id, new_pet);
        return petModel.getAll();
    }
}
