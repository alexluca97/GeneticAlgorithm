#pragma once
#include "stdafx.h"
#include"BitFunctions.h"

#define PI 3.14


using namespace std;

double function_DeJong(vector<int> vec[100], int count)
{

	double sum = 0;
	for (int i = 0; i < count; i++)
	{
		sum = sum + pow(2, ConvertToDecimal(-5.12, 5.12, vec[i]));
	}
	return sum;
}

double function_Schwefel(vector<int>vec[100], int count)
{

	int i;
	double function = 0;
	for (i = 0; i < count; i++)
	{
		function = function + (-ConvertToDecimal(-500, 500, vec[i])*(sin(convert_to_degree(sqrt(abs(ConvertToDecimal(-500, 500, vec[i])))))));
	}

	return function;
}



double function_Rastrigin(vector<int> vec[100], int count)
{
	int i;
	double sum = 0.0;
	

	for (i = 0; i < count; i++)
	{

		sum = pow(2,ConvertToDecimal(-5.12,5.12,vec[i])) - 10 * cos(convert_to_degree( 2 * PI*ConvertToDecimal(-5.12, 5.12, vec[i])));
	}

	return 10*count+sum;
	
 
}

double function_SixHump(vector<int>vec[2])
{
	int i;
	double x1,x2 ,function = 0;

	x1 = ConvertToDecimal(-3,3,vec[0]);
	x2 = ConvertToDecimal(-2,2 ,vec[1]);

	function = (4 - 2.1 * pow(x1, 2) + (pow(x1, 4) / 3))*pow(x1, 2) + x1*x2 + (-4 + 4 * pow(x2, 2))*pow(x2, 2);
	return function;
}

int function_Tema1Prim(vector<int>vec[31])
{
	int fx;
	for (int i = 0; i <= 5; i++)
	{
		fx = 0;
		cout << "x=" << i << "<====";
		fx = ConvertToDecimal(0, 31, vec[1]) * ConvertToDecimal(0, 31, vec[1]) * ConvertToDecimal(0, 31, vec[1]) - 60 * ConvertToDecimal(0, 31, vec[1]) * ConvertToDecimal(0, 31, vec[1]) + 900 * ConvertToDecimal(0, 31, vec[1]) + 100;
		cout << fx<<endl;
	}
	return fx;
}