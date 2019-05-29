#include "stdafx.h"
#include"BitFunctions.h"
#include"fitnesses.h"
#include <iostream>

using namespace std;

vector<int>* Simulated_Annealing_Schwefel(int max_number_of_iterations, int N , double temperature_step) {

	double temperature = 1.0;
	double min_fitness, fitness;
	vector<int>min_hilltop[100];
	vector <int> hilltop[100];
	vector<double>min_values_hilltops;

	for (int k = 0; k < N; k++) {
		min_hilltop[k] = GenerateRadomBitString(-32.768, 32.768, 6);
	}

	min_fitness = function_Schwefel(min_hilltop, N);

	while(temperature > 0){
	for (int i = 0; i < max_number_of_iterations; i++)
	{		
		unsigned int bit_pos = rand() % min_hilltop[0].size();
				for (int i = 0; i < N; i++) {
					hilltop[i] = Flip_bit(min_hilltop[i], bit_pos);
				}

				fitness = function_Schwefel(hilltop, N);

				if (fitness < min_fitness)
				{
					min_fitness = fitness;
					min_values_hilltops.push_back(min_fitness);
				}
				else
				{
					double probability = RandomDouble(0.0, 1.0);
					double acceptance_probability = exp((min_fitness - fitness) / temperature);
					
					if (probability < acceptance_probability)
					{
						min_fitness = fitness;
						for (int i = 0; i < N; i++) {
							min_hilltop[i] = hilltop[i];
						}
					}
				}
				temperature = temperature*temperature_step;
		}

	}

	return min_hilltop;
}

