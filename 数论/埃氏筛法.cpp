void primes(int  n)
{
	fill(v, v+n, true);
	v[0] = v[1] = false;

	int m = sqrt(n + 0.5);
	for (int i = 2; i <= m; i++)
		if (v[i])
			for(int j = i*i; j <= n; j += i)
				v[j] = false;
	//最后true为素数
}


//O（n）的线性筛
int v[MAX_N], prime[MAX_N];

void primes(int n)
{
	memset(v, 0, sizeof(v));
	int m = 0;

	for (int i = 2; i <= n; i++)
	{
		if (!v[i])
		{
			v[i] = i;
			prime[++m] = i;
		}

		for (int j = 1; j <= m; j++)
		{
			if (prime[j] > v[i] || prime[j] > n/i)	
				break;
			v[i*prime[j]] = prime[j];
		}
	}

	//prime里存放的为素数
}
