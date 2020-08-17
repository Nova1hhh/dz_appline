package ru.appline.logic;

public class User {
    private String surname;
    private String name;
    private double salary;

    public User(String surname, String name, double salary) {
        this.surname = surname;
        this.name = name;
        this.salary = salary;
    }

    public String getSurname() {
        return surname;
    }

    public String getName() {
        return name;
    }

    public double getSalary() {
        return salary;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setSalary(double salary) {
        this.salary = salary;
    }
}
