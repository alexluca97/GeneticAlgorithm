#pragma once

#include "stdafx.h"

#include "BitFunctions.h"
#include "fitnesses.h"

using namespace std;

double AdaptFitnessValue(double fitnessValue)
{
	double f;
	f = -fitnessValue;

	
		f += 5000;
	
		f = 1 / f;
	return f;
}

w
int QAP(vector<vector<int>> X)
{

	int min;
	vector<int>Container;
	int sum = 0;
	int sum2 = 0;
	for (int i = 1; i < A.size(); i++)
	{
		for (int j = 1; j < A.size(); j++)
		{
			for (int k = 1; k < A.size(); k++)
			{
				for (int l = 1; l < A.size; l++)
				{
					sum += A[i][k] * B[j][k] * X[i][j] * X[k][l];
				}
			}
		}
	}
	for (int i = 1; i < A.size(); i++)
	{
		for (int j = 1; j < A.size(); j++)
		{
			sum2 += C[i][j] + X[i][j];
		}
	}
	return sum1 + sum2;


}

vector<vector<vector<int>>>RouletteWheel_Selection(vector<vector<vector<int>>> Population, string functionName)
{
	vector<double> eval;
	vector<double>IndivSel_Probability;
	vector<double>CumulateSel_Probability;
	vector<vector<vector<int>>>SelectedPopulation;
	CumulateSel_Probability.push_back(0);
	double r = RandomDouble(0, 1);
	double totalFitness = 0;
	
		for (int i = 0; i < Population.size(); i++)
		{
			if (functionName == DJ)
			{
				eval.push_back(AdaptFitnessValue(function_DeJong(Population[i])));
			}
			else if (functionName == AK)
			{
				eval.push_back(AdaptFitnessValue(function_DeJong(Population[i])));
			}
			else if (functionName == SC)
			{
				eval.push_back(AdaptFitnessValue(function_DeJong(Population[i])));
			}
			else if (functionName == SIX)
			{
				eval.push_back(AdaptFitnessValue(function_DeJong(Population[i])));
			}
			else
			{
				cout << "Bad Function Name! \n";
			}
			totalFitness += eval[i];
		}
		for (int i = 0; i < Population.size(); i++)
		{
			IndivSel_Probability.push_back(eval[i] / totalFitness);
			CumulateSel_Probability.push_back(CumulateSel_Probability[i] + IndivSel_Probability[i]);
			
		}
		for (int i = 0; i < Population.size() ; i++)
		{
			
				if (CumulateSel_Probability[i]>= r )
				{	
					//cout << " r :   " << r << "i: " <<i<< endl;
					SelectedPopulation.push_back(Population[i]);
				}
		}
	
	return SelectedPopulation;
}




vector<vector<int>>Genetic_Algorithm(string functionName, int numberOfDimensions, int numberOfCandidates ,int numberofGenerations , double crossProb , double mutProb)
{	
	vector<vector<vector<int>>> Population = Generate_Population( numberOfDimensions, functionName, numberOfCandidates);
	vector<vector<vector<int>>> Intermediare_Population;
	vector<vector<vector<int>>> Intermediare_Population1;
	vector<vector<vector<int>>> SelectedPopulation;
	vector<vector<int>>BestCandidate;
	vector<vector<int>>BestCandidateInterm;

	vector<double>eval;
	int CurrentGen = 0;
		for (int i = 0; i < Population.size(); i++)
		{	
			if (functionName == DJ)
			{
				eval.push_back(AdaptFitnessValue(function_DeJong(Population[i])));	
			}

			else if (functionName == AK)
			{
				eval.push_back(AdaptFitnessValue(function_Ackley(Population[i])));
			}

			else if (functionName == SC)
			{
				eval.push_back(AdaptFitnessValue(function_Schwefel(Population[i])));
			}

			else if (functionName == SIX)
			{
				eval.push_back(AdaptFitnessValue(function_SixHump(Population[i])));
			}
			else
			{
				cout << "Error : Bad Name Function! \n";
			}
		}
		BestCandidate = Population[MinValueIndex(eval)];
	//	cout << "\nCandidatul " << CurrentGen + 1 <<" are fitnessul : " << AdaptFitnessValue(function_DeJong(BestCandidate)) << endl;
		eval.clear();

		while (CurrentGen < numberofGenerations)
		{
			CurrentGen++;
			SelectedPopulation = RouletteWheel_Selection(Population, functionName);
			Intermediare_Population1 = Population_After_Crossover(SelectedPopulation,crossProb);
			Intermediare_Population = Population_After_Mutation(Intermediare_Population1, mutProb);
			
			for (int i = 0; i < Intermediare_Population.size(); i++)
			{
				if (functionName == DJ)
				{
					eval.push_back(AdaptFitnessValue(function_DeJong(Intermediare_Population[i])));
					BestCandidateInterm = Intermediare_Population[MinValueIndex(eval)];
					if (AdaptFitnessValue(function_DeJong(BestCandidateInterm)) < AdaptFitnessValue(function_DeJong(BestCandidate)))
					{
						BestCandidate.clear();
						BestCandidate = BestCandidateInterm;
					/*	cout << "Candidatul " << endl;
						PrintCandidate(BestCandidate);
						cout << " are fitnessul : " << AdaptFitnessValue(function_Ackley(BestCandidate)) << endl;*/

					}
				}
				else if (functionName == AK)
				{
					eval.push_back(AdaptFitnessValue(function_Ackley(Intermediare_Population[i])));
					BestCandidateInterm = Intermediare_Population[MinValueIndex(eval)];
					if (AdaptFitnessValue(function_Ackley(BestCandidateInterm)) < AdaptFitnessValue(function_Ackley(BestCandidate)))
					{
						BestCandidate.clear();
						BestCandidate = BestCandidateInterm;
						/*cout << "Candidatul " << endl;
						PrintCandidate(BestCandidate);
						cout << " are fitnessul : " << AdaptFitnessValue(function_Ackley(BestCandidate)) << endl;*/

					}
				}
				else if (functionName == SC)
				{
					eval.push_back(AdaptFitnessValue(function_Schwefel(Intermediare_Population[i])));
					BestCandidateInterm = Intermediare_Population[MinValueIndex(eval)];
					if (AdaptFitnessValue(function_Schwefel(BestCandidateInterm)) < AdaptFitnessValue(function_Schwefel(BestCandidate)))
					{
						BestCandidate.clear();
						BestCandidate = BestCandidateInterm;
						/*cout << "Candidatul " << endl;
						PrintCandidate(BestCandidate);
						cout << " are fitnessul : " << AdaptFitnessValue(function_Schwefel(BestCandidate)) << endl;
*/
					}
				}
				else if (functionName == SIX)
				{
					eval.push_back(AdaptFitnessValue(function_SixHump(Intermediare_Population[i])));
					BestCandidateInterm = Intermediare_Population[MinValueIndex(eval)];
					if (AdaptFitnessValue(function_SixHump(BestCandidateInterm)) < AdaptFitnessValue(function_SixHump(BestCandidate)))
					{
						BestCandidate.clear();
						BestCandidate = BestCandidateInterm;
						/*cout << "\nCandidatul " << endl;
						PrintCandidate(BestCandidate);
						cout << " are fitnessul : " << AdaptFitnessValue(function_SixHump(BestCandidate)) << endl;*/

					}
				}
				else
				{
					cout << "Error : Bad Functio Name!\n";
				}
			

			}
				Population.clear();
				Population = SelectedPopulation;
				eval.clear();
				Intermediare_Population1.clear();
				Intermediare_Population1.clear();
			
		}
		return BestCandidate;

}

int main()
{

	
	
START:
	cout << endl;
	int executii ;
	int dimensiuni ;
	int nrCrom ;
	int nrGen;
	double probCross;
	double probMut;
	cout << "Dati numarul de executii : "; cin >> executii;
	cout << "Dati numarul de dimensiuni : "; cin >> dimensiuni;
	cout << "Dati numarul de cromozomi : "; cin >> nrCrom;
	cout << "Dati numarul de generatii : "; cin >> nrGen;
	cout << "Dati probabilitatea de incrucisare : "; cin >> probCross;
	cout << "Dati probabilitatea de mutatie : "; cin >> probMut;
	
	vector<double>Container;
	cout << endl;
	cout << "------------------Algoritmul genetic aplicat functiei DeJong ------------------------\n";
	cout << " Dupa " << executii << " executii cu " << dimensiuni << " dimensiuni " << " si populatie initiala de "<<nrCrom<<" cromozomi : \n";
	for (int i = 0; i < executii; i++)
	{
		vector<vector<int>>Candidate = Genetic_Algorithm(DJ, dimensiuni, nrCrom , nrGen, probCross, probMut);
		Container.push_back(AdaptFitnessValue(function_DeJong(Candidate)));
	}
	cout << " Minimul : "<< MinValue(Container) << endl;
	cout << " Maximul : "<<MaxValue(Container)<<endl;
	cout << " Media : " << ((MinValue(Container) + MaxValue(Container))/2) << endl;
	cout << endl;

	Container.clear();

	cout << "------------------Algoritmul genetic aplicat functiei Ackley ------------------------\n";
	cout << " Dupa " << executii << " executii cu " << dimensiuni << " dimensiuni  " << " si populatie initiala de " << nrCrom << " cromozomi : \n";
	for (int i = 0; i < executii; i++)
	{
		vector<vector<int>>Candidate = Genetic_Algorithm(AK, dimensiuni, nrCrom, nrGen, probCross, probMut);
		Container.push_back(AdaptFitnessValue(function_Ackley(Candidate)));
	}
	cout << " Minimul : "<<MinValue(Container) << endl;
	cout << " Maximul : " << MaxValue(Container) << endl;
	cout << " Media : " << ((MinValue(Container) + MaxValue(Container))/2) << endl;
	cout << endl;

	Container.clear();
	cout << "------------------Algoritmul genetic aplicat functiei SixHump ------------------------\n";
	cout << " Dupa " << executii << " executii cu " << dimensiuni << " dimensiuni  " << " si populatie initiala de " << nrCrom << " cromozomi : \n";
	for (int i = 0; i < executii; i++)
	{
		vector<vector<int>>Candidate = Genetic_Algorithm(SIX, dimensiuni, nrCrom, nrGen, probCross, probMut);
		Container.push_back(AdaptFitnessValue(function_SixHump(Candidate)));
	}
	cout << " Minimul : "<< MinValue(Container) << endl;
	cout << " Maximul : " << MaxValue(Container) << endl;
	cout << " Media : " << ((MinValue(Container) + MaxValue(Container))/2) << endl;
	cout << endl;

	Container.clear();

	cout << "------------------Algoritmul genetic aplicat functiei Schwefel ------------------------\n";
	cout << " Dupa " << executii << " executii cu " << dimensiuni << " dimensiuni  " << " si populatie initiala de " << nrCrom << " cromozomi : \n";
	for (int i = 0; i < executii; i++)
	{
		vector<vector<int>>Candidate = Genetic_Algorithm(SC, dimensiuni, nrCrom, nrGen, probCross, probMut);
		Container.push_back(AdaptFitnessValue(function_Schwefel(Candidate)));
	}
	cout << " Minimul : " << MinValue(Container) << endl;
	cout << " Maximul : " << MaxValue(Container) << endl;
	cout << " Media : " << ((MinValue(Container) + MaxValue(Container))/2) << endl;
	cout << endl;
	Container.clear();

	cout << endl;

	cout << "Vreti sa incercati o noua executie a programului cu alti paramatri? (Y/N)\n";
	AGAIN:
	string command ; 
	cin >> command;
	if (command == "Y")
	{
		goto START;
	}
	else if(command =="N")
	{
		return 0;
	}
	else
	{
		cout << "Commanda gresita ,incercati din nou ! \n";
		goto AGAIN;
	}

	
}

