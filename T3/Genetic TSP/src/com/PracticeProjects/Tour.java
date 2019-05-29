package com.PracticeProjects;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Line2D;
import java.util.ArrayList;

//import static com.PracticeProjects.Main.frame;

public class Tour extends JPanel{

    private ArrayList<Town> tourCitys;
    private float fitness = 0;
    private float distance = 0;


    public Tour(){
        tourCitys = new ArrayList<Town>();
        fitness = 0;
        distance = 0;
    }

    void add(Town A)
    {
        tourCitys.add(A); //Adaugam un oras la turneu
    }

    public ArrayList<Town> getTourCitys() {
        return tourCitys;
    }

    public float getDistance()
    {
        if (this.distance == 0)
            calculateDistance();    //Calculam distanta daca ea este 0(adica nu a fost calculata niciodata))

        return this.distance;
    }

    public float getFitness()   //Daca fitness este 0 il calculam.
    {
        if (this.fitness == 0)
        {
            if (this.distance == 0)
                calculateDistance();
			this.fitness=1.0f/this.distance * 500;
            return fitness;
        }
        return fitness;
    }

    private void calculateDistance()
    {
        for (int i = 0; i < tourCitys.size() - 1; i++)
        {
            distance += tourCitys.get(i).cityDistane(tourCitys.get(i+1));
        }
    }
}
