package com.PracticeProjects;

public class Town {

    private final int x;
    private final int y;
    private final String name;

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        System.out.println(name + " (" + x + ", " + y + ")");
        return(name + " (" + x + ", " + y + ")\n");
    }

    public Town(String name, int x, int y) {
        this.x = x;
        this.y = y;
        this.name = name;
    }

    public float cityDistane(Town city)
    {
        return (float)Math.sqrt((this.x - city.getX()) * (this.x - city.getX()) + (this.y - city.getY()) * (this.y - city.getY())); //Distanta dintre 2 orase cu formula pitzi
    }
}
