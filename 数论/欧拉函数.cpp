//O(√n)求n的欧拉函数值
int euler_phi(int n)
{
	int res = n;

	for (int i = 2; i*i < n; i++)
		if (n % i == 0)
		{
			res = res / i * (i-1);
			while (n % i == 0)	n /= i;
		}

	if (n != 1)	res = res / n * (n-1);
	return res;
}

//O(nlogn)筛法求0~n的所有欧拉函数值
void euler_phi2()
{
	int euler[MAX_N + 1];

	for (int i = 0; i <= n; i++)	euler[i] = i;
	for (int i = 2; i <= n; i++)
		if (euler[i] == i)
			for (int j = i; j <= n; j += i)
				euler[j] = euler[j] / i * (i-1);
}

//O(n)线性筛2~n的所有欧拉函数值
//性质4：若p | n，且p² | n，φ（n）= φ（n/p）* p
//性质5：若p | n，但p²不整除n，φ（n）= φ（n/p）*（p-1）
int v[MAX_N], prime[MAX_N], euler[MAX_N];
void euler_phi3()
{
	memset(v, 0, sizeof(0));
	int m = 0;
	for (int i = 2; i <= n; i++)
	{
		if (!v[i])
		{
			v[i] = i;
			prime[++m] = i;
			euler[i] = i - 1;
		}

		for (int j = 1; j <= m; j++)
		{
			if (prime[j] > v[i] || prime[j] * i > n)	break;
			v[i * prime[j]] = prime[j];
			euler[i * prime[j]] = euler[i] * (i % prime[j] ? prime[j] - 1 : prime[j]);
		}
	}
}