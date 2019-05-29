#pragma once
#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm> 
#include <bitset>
#include <math.h>


#define DJ "DeJong"
#define SC "Schwefel"
#define AK "Ackley"
#define SIX "SixHump"

using namespace std;

double convert_to_degree(double val) {
	double result = 0;
	result = tan(val * 3.14159265 / 180);
	return result;
}

double RandomDouble(double a, double b) {
	double random = ((double)rand()) / (double)RAND_MAX;
	double diff = b - a;
	double r = random * diff;
	return a + r;
}

vector<int> GenerateRadomBitString(string functionName) {
	vector<int> vec;
	int d = 6;
	int a, b;
	if (functionName.compare(DJ) !=0 && functionName.compare(AK) != 0 &&  functionName.compare(SC) != 0 && functionName.compare(SIX) != 0 ){
		cout << "Error : bad function name! \n";
		exit(0);
	}
	if (functionName.compare(DJ)== 0) {
		a = -5.12;
		b = 5.12;
	}
	else if(functionName.compare(SC)==0) {
		a = -500;
		b = 500;
	}
	else if(functionName.compare(AK)==0) {
		a = -32.768;
		b = 32.768;
	}
	else {
		a = -3;
		b = 3;
	}
	int N = (b - a) * pow(10, d);
	int n = round(log2(N));

	for (int i = 0; i < n; i++)
	{
		vec.push_back(rand() % 2);
	}
	return vec;
}

vector<vector<int>>Generate_Candidate(int dimensions , string functionName)
{	
	vector<vector<int>> Candidate;
	for (int i = 0; i < dimensions; i++)
	{
		Candidate.push_back(GenerateRadomBitString(functionName));
	}
	return Candidate;
}

vector<vector<vector<int>>>Generate_Population(int dimensions, string functionName ,int numberOfCandidates)
{	

	vector<vector<vector<int>>>Population;
	for (int i = 0; i < numberOfCandidates; i++)
	{
		Population.push_back( Generate_Candidate(dimensions, functionName));
	}
	return Population;
}

void PrintGene(vector<int>cromozome)
{
	for( int i = 0; i < cromozome.size(); i++)
	{
		cout << cromozome[i];
	}
}

void PrintCandidate(vector<vector<int>>My_Population)
{
	for (int i = 0; i < My_Population.size(); i++)
	{
		for (int j = 0; j < My_Population[i].size(); j++)
		{
			cout << My_Population[i][j];
		}
		cout << endl;
	}
}
void PrintPop(vector<vector<vector<int>>> MyPopulation)
{
	for (int i = 0; i < MyPopulation.size(); i++)
	{
		PrintCandidate(MyPopulation[i]);
		cout<<endl;
	}
}
double ConvertToDecimal(double a, double b, vector<int> vec) {
	int nr = 0;
	reverse(vec.begin(), vec.end());
	if (vec[0] == 1)
		nr++;
	for (int i = 1; i < vec.size(); i++) {
		if (vec[i] == 1)
			nr = nr + pow(2, i);
	}
	return a + nr*(b - a) / (pow(2, vec.size()) - 1 );
}

double MinValue(vector<double> vec) {
	double min = vec[0];
	
	for (int i = 1; i < vec.size(); i++) {

		if (vec[i]<min)
		{
			min = vec[i];
		
		}
	}

	return min;
}

double MinValueIndex(vector<double> vec) {
	double min = vec[0];
	int index = 0 ;
	for (int i = 1; i < vec.size(); i++) {

		if (vec[i]<min)
		{
			min = vec[i];
			index = i;
		}
	}

	return index;
}


double MaxValue(vector<double> vec) {
	double max= vec[0];
	for (int i = 1; i < vec.size(); i++) {

		if (vec[i] > max)
		{
			max = vec[i];
		}
	}

	return max;
}


void Mutation(vector <int> &gene, int bit_position) {
	if (gene[bit_position] == 0) {
		gene[bit_position] = 1;
	}
	else if (gene[bit_position] == 1) {
		gene[bit_position] = 0;
	}
	else
		cout << "Eroare, vector gresit! " << endl;
}
void MutationCandidate(vector<vector<int >> &cromozome, int bit_position)
{
	for (int i = 0; i < cromozome.size(); i++) {
		for (int j = 0; j < cromozome[i].size(); j++)
		{
			if (bit_position == j)
				Mutation(cromozome[i],j);
		}
	}
}

vector<vector<vector<int>>>Population_After_Mutation(vector<vector<vector<int>>>MyPopulation, double mutProb)
{
	double r = 0;
	int  k = 0;
	
	for (int i = 0; i < MyPopulation.size(); i++)
	{
		//int bit_pos = rand() % (MyPopulation[i][0].size() - 1 + 1);
		//cout << "Mutation at point : " << bit_pos << endl;
		
			for (int j = 0; j < MyPopulation[i][0].size(); j++)
			{
				r = RandomDouble(0, 1);

				if (r < mutProb) {
					MutationCandidate(MyPopulation[i], j);
					
				}
				
			}
		
		}
	
	
	return MyPopulation;
}

void Crossover(vector<int>&firstCrom, vector<int>&secondCrom,int bit_position)
{
	vector<int> FirstHalf1, SecondHalf1, FirstHalf2, SecondHalf2, Composer;
	for (int i = 0; i <= bit_position; i++)
	{
		FirstHalf1.push_back(firstCrom[i]);
		FirstHalf2.push_back(secondCrom[i]);
	}
	for (int i = bit_position + 1; i < firstCrom.size(); i++)
	{
		SecondHalf1.push_back(firstCrom[i]);
		SecondHalf2.push_back(secondCrom[i]);
	}
	Composer = FirstHalf1;
	Composer.insert(Composer.end(), SecondHalf2.begin(), SecondHalf2.end());
	firstCrom = Composer;
	Composer.clear();
	Composer = FirstHalf2;
	Composer.insert(Composer.end(), SecondHalf1.begin(), SecondHalf1.end());
	secondCrom = Composer;
}

vector<vector<vector<int>>> Population_After_Crossover(vector<vector<vector<int>>>MyPopulation , double crossProb)
{
	
	vector<int> markedIndexs;
	int j = 0;
	int indexwhereCross = 0;
	for (int k = 0; k < MyPopulation.size(); k++)
	{	
		double r = RandomDouble(0, 1);
	
		
		if (r < crossProb)
		{    
			/*cout << "iNDIVIDUL SELECTAT : " << k << "CU R : " << r << endl;*/
			for (int i = 0; i < MyPopulation[k].size(); i++)
			{
				if (find(markedIndexs.begin(), markedIndexs.end(), i) != markedIndexs.end() || (markedIndexs.size()==MyPopulation[k].size()-1))
				{
					goto FORFINAL;
				}
				if (i == MyPopulation[k].size() / 2)
				{

				}
			SEARCH:
				j = rand() % (MyPopulation[k].size());
				if (find(markedIndexs.begin(), markedIndexs.end(), j) != markedIndexs.end() || i == j || j==0 )
				{
					goto SEARCH;
				}

				indexwhereCross = rand() % MyPopulation[k][i].size();
				/*cout << endl;
				cout << "Am incrucisat la punctul : " << indexwhereCross << endl;
				cout << " Cromozomii : " << i << " si " << j <<endl;
				PrintGene(MyPopulation[k][i]);
				cout << endl;
				cout << "si " << endl;
				PrintGene(MyPopulation[k][j]);*/
				Crossover(MyPopulation[k][i], MyPopulation[k][j], indexwhereCross);
			/*	cout << endl;
				cout << "Rezultat : " << endl;
				PrintGene(MyPopulation[k][i]);
				cout << endl;
				cout << "si " << endl;
				PrintGene(MyPopulation[k][j]);*/
				markedIndexs.push_back(i);
				markedIndexs.push_back(j);

			FORFINAL:
				j++;
			}
			markedIndexs.clear();
		}
	}
	
	return MyPopulation;
}


