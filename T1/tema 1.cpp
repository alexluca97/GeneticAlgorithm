#include "stdafx.h"
#include"BitFunctions.h"
#include"fitnesses.h"
#include <iostream>
#include <time.h>

#define DJ "DeJong"
#define SC "Schwefel"
#define RA "Rastrigin"
#define SIX "SixHump"
#define TeP "Tema1Prim"
#define TEMP_STEP 0.95


double function_fitness(vector<int>vec[100], int N, string functionName) {
	if (functionName != DJ && functionName != SC && functionName != RA && functionName != SIX && functionName != TeP)
	{
		cout << "Error : bad function name! \n";
		exit(1);
	}
	if (functionName.compare(DJ) == 0) {
		return function_DeJong(vec, N);
	}
	else if (functionName.compare(SC) == 0) {
		return function_Schwefel(vec, N);
	}
	else if (functionName.compare(RA) == 0) {
		return function_Rastrigin(vec, N);
	}
	else if (functionName.compare(TeP) == 0) {
		return function_Tema1Prim(vec);
	}
	else
	{
		return function_SixHump(vec);
	}

}

vector<double> Steepest_Ascent_Hill_Climbing(int max_number_of_iterations, int N , string functionName )//flip random
{

	vector<int>min_hilltop[100];
	vector <int> hilltop[100];
	vector<double>min_values_hilltops;
	double min_fitness, fitness;
	int found;

	srand(time(NULL));
	for (int i = 0; i < max_number_of_iterations; i++)
	{
		for (int k = 0; k < N; k++) {
			
			min_hilltop[k] = GenerateRadomBitString(functionName);
		}
		min_fitness = function_fitness(min_hilltop, N ,functionName);
		
		found = 1;
		while (found)
		{
			found = 0;
			for (int j = 0; j < min_hilltop[0].size(); j++) {
				for (int i = 0; i < N; i++) {
					hilltop[i] = Flip_bit(min_hilltop[i], j);
				}
				fitness = function_fitness(hilltop, N , functionName);
				if (fitness < min_fitness)
				{
					min_fitness = fitness;
					min_values_hilltops.push_back(min_fitness);
					found = 1;
				}
			}
		}
	
	}

	return min_values_hilltops;
}

vector<double> Next_Ascent_Hill_Climbing(int max_number_of_iterations, int N, string functionName) {

	vector<int>max_hilltop[100];
	vector <int> hilltop[100];
	vector<double>min_values_hilltops;
	double max_fitness, fitness;
	
	srand(time(NULL));

	for (int i = 0; i < max_number_of_iterations; i++)
	{
		for (int k = 0; k < N; k++) {
			max_hilltop[k] = GenerateRadomBitString(functionName);
		}
		max_fitness = function_fitness(max_hilltop, N, functionName);

			for (int j = 0; j < max_hilltop[0].size(); j++) {
				for (int i = 0; i < N; i++) {
					hilltop[i] = Flip_bit(max_hilltop[i], j);
				}
				fitness = function_fitness(hilltop, N, functionName);
				if (fitness < max_fitness)
				{
					max_fitness = fitness;
					min_values_hilltops.push_back(max_fitness);
			}
		}

	}

	return min_values_hilltops;
}


/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/

//Simulated Annealing implementation :


vector<double> Simulated_Annealing(int max_number_of_iterations, int N, double temperature_step ,string functionName) {

	double temperature = 1000.0;
	double max_fitness, fitness;
	vector<int>max_hilltop[100];
	vector <int> hilltop[100];
	vector<double>min_values_hilltops;

	int count = 0;

	srand(time(NULL));

	for (int k = 0; k < N; k++) {
		max_hilltop[k] = GenerateRadomBitString(functionName);
	}
	max_fitness = function_fitness(max_hilltop, N , functionName);

	while (temperature > 1) {
		for (int i = 0; i < max_number_of_iterations; i++)
		{
			unsigned int bit_pos = rand() % max_hilltop[0].size();
			for (int i = 0; i < N; i++) {
				hilltop[i] = Flip_bit(max_hilltop[i], bit_pos);
			}

			fitness = function_fitness(hilltop, N , functionName);

			if (fitness < max_fitness)
			{

				max_fitness = fitness;
				min_values_hilltops.push_back(max_fitness);
			}
			else
			{
				double probability = RandomDouble(0.0, 1.0);
				double acceptance_probability = exp((max_fitness - fitness) / temperature);

				if (probability < acceptance_probability)
				{
					max_fitness = fitness;
					min_values_hilltops.push_back(max_fitness);
					for (int i = 0; i < N; i++) {
						max_hilltop[i] = hilltop[i];
					}
				}
			}
			temperature = temperature*temperature_step;
		}
	}
	return min_values_hilltops;
}

void citire(vector<double> vec) {
	for (int i = 0; i < vec.size(); i++) {
	cout << vec[i];
	cout << endl;
	}
}
/*int main() 
{	
	

	int a, b;
	
	
	cout << " Dati nr maxim  de iteratii : "<<endl; cin >> a;
	cout << " Dati nr maxim  de variabile : " << endl; cin >> b;
		cout << " De Jong : " << endl;
		cout << "Steepest Ascent" << endl;
		cout << "Valoare minima " << MinValue(Steepest_Ascent_Hill_Climbing(a, b, DJ)) << endl;



		cout << "Next Acent :" << endl;
		cout << "Valoare minima " << MinValue(Next_Ascent_Hill_Climbing(a, b, DJ)) << endl;
		
		cout << "===========================================================" << endl;
		cout << " Schwefel : " << endl;
		cout << "Steepest Next Ascent" << endl;
		cout << "Valoare minima " << MinValue(Steepest_Ascent_Hill_Climbing(a, b, SC)) << endl;

		cout << "Next Acent :" << endl;
		cout << "Valoare minima " << MinValue(Next_Ascent_Hill_Climbing(a, b, SC)) << endl;
		
		cout << "===========================================================" << endl;
		cout << " Rastrigin : " << endl;
		cout << "Steepest Ascent" << endl;
		cout << "Valoare minima " << MinValue(Steepest_Ascent_Hill_Climbing(a, b, RA)) << endl;
	
		cout << "Next Acent :" << endl;
		cout << "Valoare minima " << MinValue(Next_Ascent_Hill_Climbing(a, b, RA)) << endl;


		cout << "===========================================================" << endl;
		cout << " Six Hump Camel Back : " << endl;

		cout << "Steepest  Ascent" << endl;
		cout << "Valoare minima  " << MinValue(Steepest_Ascent_Hill_Climbing(a, b, SIX)) << endl;


		cout << "Next Acent :" << endl;
		cout << "Valoare minima " << MinValue(Next_Ascent_Hill_Climbing(a, b, SIX)) << endl;
		
		cout << " ===========================================================" << endl;
		cout << " ===========================================================" << endl;
		cout << " ===========================================================" << endl;

		cout << "SIMULATED ANNEALING " << endl;
		cout << " De Jong : " << endl;
	
		cout << "Valoare minima " << MinValue(Simulated_Annealing(a, b, TEMP_STEP, DJ)) << endl;
		
		cout << " ===========================================================" << endl;
		cout << "Schwefel " << endl;
		
		cout << "Valoare minima " << MinValue(Simulated_Annealing(a, b, TEMP_STEP, SC)) << endl;
	
		cout << " ===========================================================" << endl;
		cout << "Rastrigin " << endl;
		
		cout << "Valoare minima " << MinValue(Simulated_Annealing(a, b, TEMP_STEP, RA)) << endl;
	
		cout << " ===========================================================" << endl;
		cout << "SixHump " << endl;
		
		cout << "Valoare minima " << MinValue(Simulated_Annealing(a, 2, TEMP_STEP, SIX)) << endl;
		
	

	return 0;
}*/
int main()
{
	int a = 100;
		cout << MaxValue(Steepest_Ascent_Hill_Climbing(a, 31, TeP))<<endl;
	return 0;
}