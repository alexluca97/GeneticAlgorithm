package com.PracticeProjects;

import javax.swing.*;
import java.awt.*;

public class Main {
   //public static JFrame frame = new JFrame("Lines");

    public static void main(String[] args) {
        //frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //frame.setSize(800, 800);
        //frame.setLocationRelativeTo(null);


        GeneticSolver S = new GeneticSolver();
        S.evolve();
       System.out.println("vs Eurisitc");
        S.euristic();

    }
}
