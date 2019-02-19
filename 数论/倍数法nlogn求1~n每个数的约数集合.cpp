std::vector<int> factor[MAX_N];

void Factors(int n)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n/i; j++)
			factor[i*j].push_back(i);
}