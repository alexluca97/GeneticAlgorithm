package com.PracticeProjects;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

//import static com.PracticeProjects.Main.frame;


public class GeneticSolver {
    private static final String[] cityNames = {"Stony Prairie", "Oilton", "Glen Rose", "Oak Hall", "Rainelle", "Deer Lick", "Damar", "Penbrook", "Encinal", "Ebensburg", "West Okoboji", "Roan Mountain", "Selawik", "Hanska", "Delafield", "Meta", "Arkadelphia", "Amite City", "Cato", "Hutchins", "Cashmere", "Green Bay", "Pajaro Dunes", "Norwalk", "Seco Mines", "Cheyenne Wells", "McGrath", "Howe", "Benavides", "Honeyville", "Cimarron", "Brice Prairie", "Blades", "Breesport", "Porum", "Southfield", "Black Hawk", "Mount Victory", "Gervais", "Mystic", "Anaconda", "Highland Springs", "Kline", "Tangier", "Yankee Lake", "Cusseta", "Arab", "North El Monte"};
    private static ArrayList<String> usedNames = new ArrayList<String>(cityNames.length);
    private static final boolean IS_TURNEU = true;
    private static final int NR_CROMOZOMI = 1000; //numarul de tururi
    private static final int NR_GENE = 40;  //nr de orase in tur
    private static final int NR_GENERATII = 1000;  //iteratii
    private static final float MUTATION_CHANCE = 0.02f;   //Rata de mutatie 2%
    private static final float CROSSOVER_CHANCE = 0.9f;   // Rata de crossover 90%
    private static final int OFFSET = 1000;   //coordonatele x si y in intervalul [0-1000]
    private static float min = 0xfffffff;     // minimul nostru actual


    private Tour minTour;

    private ArrayList<Tour> population;

    private void initPop()
    {
        Tour T;
        Town t;
        population = new ArrayList<Tour>(NR_CROMOZOMI);
        Random r = new Random();
        for (int i = 0; i < NR_CROMOZOMI; ++i)
        {
             T = new Tour();

            for (int j = 0; j < NR_GENE; ++j)
            {
                for (int k = 0; k < 5000; ++k)
                {
                    int indx = r.nextInt(cityNames.length);    // avem un index intre 0-50(Nr de orase)
                    if (!usedNames.contains(cityNames[indx]) || k == 4999) // verificam s-a mai ales o data orasul
                    {
                        t = new Town(cityNames[indx], r.nextInt(OFFSET), r.nextInt(OFFSET));// Random nume,x,y
                        T.add(t);   //Adaugam in tur
                        usedNames.add(cityNames[indx]);  //adaugam numele la "nume folosite"
                        k = 6000;
                    }
                }

            }
            //System.out.println("-----");
            population.add(T);      //Adaugam la populatie turul generat
        }
    }
    private void mutate(Tour tour) //Permutam 2 orase random
    {
        Random r = new Random();

        int index1 = r.nextInt(tour.getTourCitys().size());
        int index2 = (index1 + r.nextInt(tour.getTourCitys().size()) + 1) % tour.getTourCitys().size(); //make sure they are different

        Collections.swap(population, index1, index2);
    }
    private Tour choseRandomByFitness()
    {
        int beSafe = 0;
        Random r1 = new Random();
        Random r2 = new Random();
        while(beSafe < 10000)
        {
            int index = r1.nextInt(population.size());

            float reqFit = r2.nextFloat() + 0.000001f;  //Alegem turul cu fitness-ul cel mai mare

            if (population.get(index).getFitness() >= reqFit) {
                return population.get(index);
            }

            beSafe++;
        }
        System.out.println("SOMETHING WENT WRONG IN CHOSE RANDOM BY FITNESS");
        return population.get(r1.nextInt(population.size()));
    }
    private void selection()  //alegem 2 turnee si comparam fitness-ul si il pastram pe cel cu fitness mai mare
    {
        ArrayList<Tour> selectedPop = new ArrayList<Tour>(population.size()); //initializare
        if(IS_TURNEU == true) {//

            Random r = new Random();

            for (int i = 0; i < population.size(); i++) {

                Tour cromozom1 = choseRandomByFitness();
                Tour cromozom2 = choseRandomByFitness();

                if (cromozom1.getFitness() > cromozom2.getFitness()) {
                    selectedPop.add(cromozom1);
                } else {
                    selectedPop.add(cromozom2);
                }
            }
        }
        else { //roata norocului

            float total_fitness = 0;
            float[] p = new float[population.size()];
            float[] q = new float[population.size() + 1];
            for (Tour it : population) {
                total_fitness += it.getFitness();
            }
            int i = 0;
            for (Tour it : population) {
                p[i++] = it.getFitness() / total_fitness;
            }

            q[0] = 0;
            for (i = 0; i < population.size(); i++) {
                q[i + 1] = q[i] + p[i];
            }
            Random r = new Random();
            float temp;
            int j = 0;
            for (i = 0; i < population.size(); i++) {
                boolean ok = true;
                while(ok){
                    //System.out.println("sal " + j + " " + population.size() );
                    temp = r.nextFloat();
                    if (q[j] < temp && temp <= q[j+1])
                    {
                        ok = false;
                        selectedPop.add(population.get(j));
                    }
                    else
                    if (j > population.size() - 1)
                    {
                        selectedPop.add(choseRandomByFitness());
                        break;
                    }

                    j++;
                }
            }

        }
        population.clear();
        population.addAll(selectedPop);

    }
    private void crossOver()  //
    {
        ArrayList<Tour> newPop = new ArrayList<Tour>();
        Random r = new Random();

        for (int i = 0; i < population.size(); ++i)
        {

            Tour A = choseRandomByFitness();
            if (Math.random() < CROSSOVER_CHANCE)
            {
                Tour B = choseRandomByFitness();

                Tour newTour = new Tour();

                int fromIndex = r.nextInt(A.getTourCitys().size()); //a[100] x b[100] = c[100] Fara repetari 
                int toIndex = r.nextInt(A.getTourCitys().size());

                if (fromIndex > toIndex)
                {
                    int temp = fromIndex;
                    fromIndex = toIndex;
                    toIndex = temp;
                }
                for (int j = 0; j < A.getTourCitys().size(); ++j)
                {
                    if (j >= fromIndex && j <= toIndex)
                        newTour.add(A.getTourCitys().get(j));
                    else
                        newTour.add(B.getTourCitys().get(j));
                }

                if (Math.random() < MUTATION_CHANCE)  //Vedem daca avem sansa de mutatie, daca avem o facem
                {
                    mutate(newTour);
                }

                newPop.add(newTour);
            }
            else
            {
                if (Math.random() < MUTATION_CHANCE)
                {
                    mutate(A);
                }
                newPop.add(A);
            }

        }

        population.clear();
        population.addAll(newPop);

    }
  /*  private void crossOver2()
    {
        ArrayList<Tour> newPop = new ArrayList<Tour>();
        Random r = new Random();

        ArrayList<Town> substrA = new ArrayList<Town>();
        ArrayList<Town> substrB = new ArrayList<Town>();

        for (int i = 0; i < population.size(); ++i)
        {

            Tour A = choseRandomByFitness();
            if (Math.random() < CROSSOVER_CHANCE)
            {
                Tour B = choseRandomByFitness();

                Tour newTour = new Tour();

                int fromIndex = r.nextInt(A.getTourCitys().size());
                int toIndex = r.nextInt(A.getTourCitys().size());

                if (fromIndex > toIndex)
                {
                    int temp = fromIndex;
                    fromIndex = toIndex;
                    toIndex = temp;
                }
                for (int j = 0; j < A.getTourCitys().size(); ++j)
                {
                    if (j >= fromIndex && j <= toIndex)
                    {
                        substrA.add(A.getTourCitys().get(j));
                        substrB.add(B.getTourCitys().get(j));
                    }
                    //else
                    //    newTour.add(B.getTourCitys().get(j));
                }

                int ok = 1;
                int j = 0;
                while (ok == 1)
                {
                    if (substrA.get(j).cityDistane(substrB.get(j+1)) > minTour.getTourCitys().lastIndexOf(substrA.get(1)));
                    {
                        ok = 0;
                    }

                }

                if (Math.random() < MUTATION_CHANCE)
                {
                    mutate(newTour);
                }

                newPop.add(newTour);
            }
            else
            {
                if (Math.random() < MUTATION_CHANCE)
                {
                    mutate(A);
                }
                newPop.add(A);
            }

        }

        population.clear();
        population.addAll(newPop);

    }*/
    private void mutate2(Tour tour)
    {
        Random r = new Random();

        int index1 = r.nextInt(tour.getTourCitys().size());
        int index2 = (index1 + r.nextInt(tour.getTourCitys().size()) + 1) % tour.getTourCitys().size(); //make sure they are different

        if (index1 > index2)
        {
            int temp = index2;
            index2 = index1;
            index1 = temp;
        }

        for (int i = index1; i < index2; i++)
        {
            Collections.swap(population, i, index2);
            --index2;
        }

    }
    private void updateMin()
    {
        for (Tour T : population)
        {
            if (T.getDistance() < min)
            {
                min = T.getDistance();
                System.out.println("Min updated to: " + min);

                minTour = T;
            }
        }
    }

    public void evolve()
    {
        initPop();

        for (int index = 0; index < NR_GENERATII; ++index)
        {
            //System.out.println(index);
            selection();
            crossOver(); // + mutation here
            updateMin();
           // draw();
        }
            for (Town t : minTour.getTourCitys())
            {
                t.toString();
            }
    
    }

    public void euristic()
    {
       initPop();
       min = 0xfffffff;
       for (Tour t : population)
       {
           Collections.shuffle(t.getTourCitys());
           updateMin();
       }

    }

}
