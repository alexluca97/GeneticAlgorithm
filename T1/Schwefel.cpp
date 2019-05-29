double function_Schwefel(vector<int> vec[100], int count)
{

	int i;
	double function = 0;
	for (i = 0; i < count; i++)
	{
		function = function + (-ConvertToDecimal(-500, 500, vec[i])*(sin(convert_to_degree(sqrt(abs(ConvertToDecimal(-500, 500, vec[i])))))));
	}

	return function;
}
