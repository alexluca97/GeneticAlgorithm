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
#define RA "Rastrigin"
#define SIX "SixHump"
#define TeP "Tema1Prim"

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
	if (functionName.compare(DJ) !=0 && functionName.compare(RA) != 0 &&  functionName.compare(SC) != 0 && functionName.compare(SIX) != 0 && functionName.compare(TeP) != 0){
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
	else if(functionName.compare(RA)==0) {
		a = -5.12;
		b = 5.12;
	}
	else if (functionName.compare(TeP)==0)
	{
		a = 0;
		b = 31;
	}
	else
	{
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

vector<vector<int>>Generate_Population(int n , string functionName)
{	
	vector<vector<int>> My_Population;
	for (int i = 0; i < n; i++)
	{
		My_Population.push_back(GenerateRadomBitString(functionName));
	}
	return My_Population;
}

void PrintPopulation(vector<vector<int>>My_Population)
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


vector<int>Flip_bit(vector <int> max_hilltop, int bit_position) {
	if (max_hilltop[bit_position] == 0) {
		max_hilltop[bit_position] = 1;
	}
	else if (max_hilltop[bit_position] == 1) {
		max_hilltop[bit_position] = 0;
	}
	else
		cout << "Eroare, vector gresit! " << endl;

	return max_hilltop;
}
