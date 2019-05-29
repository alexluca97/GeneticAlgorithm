
double function_Ackley(vector<int> vec[100], int count)
{
	int i;
	float function = 0, sum1 = 0, sum2 = 0;
	int a = 20;
	float b = 0.2;
	float c = 2 * PI;

	for (i = 0; i < count; i++)
	{

		sum1 = sum1 + pow(ConvertToDecimal(-32.768, 32.768, vec[i]), 2);
		sum2 = sum2 + cos(convert_to_degree(c*ConvertToDecimal(-32.768, 32.768, vec[i])));
	}

	function = -a*exp(-b*sqrt(1 / count*sum1)) - exp(1 / count)*sum2 + a + exp(1);
	return function;
}