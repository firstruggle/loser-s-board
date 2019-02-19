bool isprime(int n)
{
	int m = floor(sqrt(n)+0.5);
	for (int i = 2; i <= m; i++)
		if (n%i == 0)
			return false;
	return n > 1;
}