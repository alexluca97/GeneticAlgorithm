#pragma once
#include "stdafx.h"
#include"BitFunctions.h"

#define PI 3.14


using namespace std;

double function_DeJong(vector<vector<int>>vec )
{
	
	double sum = 0;
	for (int i = 0; i < vec.size(); i++)
	{	
		sum = sum + pow(2, ConvertToDecimal(-5.12, 5.12, vec[i]));
	}
	return sum;
}

double function_Schwefel(vector<vector<int>>vec)
{

	int i;
	double function = 0;
	for (i = 0; i < vec.size(); i++)
	{
		function = function + (-ConvertToDecimal(-500, 500, vec[i])*(sin(convert_to_degree(sqrt(abs(ConvertToDecimal(-500, 500, vec[i])))))));
	}

	return function;
}



double function_Ackley(vector<vector<int>>vec)
{
	int i;
	double sum1 = 0.0, sum2 = 0.0;
	

	for (i = 0; i < vec.size(); i++)
	{

		sum1 = sum1 + pow(ConvertToDecimal(-32.768, 32.768, vec[i]), 2);
		sum2 = sum2 + cos((2* PI*ConvertToDecimal(-32.768, 32.768, vec[i]))*(180.0/ PI));
	}

	return -20*exp(-0.2*sqrt(sum1/vec.size())) - exp(sum2/vec.size()) + 20 + exp(1);
	
 
}

double function_SixHump(vector<vector<int>>vec)
{
	int i;
	double x1,x2 ,function = 0;

	x1 = ConvertToDecimal(-3,3,vec[0]);
	x2 = ConvertToDecimal(-2,2 ,vec[1]);

	function = (4 - 2.1 * pow(x1, 2) + (pow(x1, 4) / 3))*pow(x1, 2) + x1*x2 + (-4 + 4 * pow(x2, 2))*pow(x2, 2);
	return function;
}