

double function_DeJong(vector<int> vec[100], int count)
{

	double sum = 0;
	for (int i = 0; i < count; i++)
	{
		sum = sum + pow(2, ConvertToDecimal(-5.14, 5.14, vec[i]));
	}
	return sum;
}
