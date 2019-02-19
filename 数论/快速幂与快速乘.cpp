//快速幂：x^n%mod
long long mod_pow(long long x, long long n, long long mod)
{
	long long res = 1;
	while (n)
	{
		if (n & 1)
			res = res*x%mod;
		x = x*x%mod;
		n >>= 1;
	}
	return res;
}

//快速乘a*b%mod
long long mod_mul(long long a, long long b, long long mod)
{
	long long ans=0;
	while(b)
	{
		if (b & 1)
			ans=(ans + a)%mod;
		a = 2*a%mod;
		b >>= 1;
	}
	return ans;
}

//一行快速乘O(1)
long long quick_mul(long long a, long long b,long long mod)
{
	return ((a*b-(long long)(((long double)a*b+0.5)/mod)*mod)%mod+mod)%mod;
}

//算法进阶指南的快速乘
long long quick_mul(long long a, long long b, long long mod)
{
	a%=mod,b%=mod;
	long long c = (long double)a*b/mod;
	long long ans = a*b - c*mod;
	if (ans < 0)	
		ans += mod;
	else if (ans > 0)
		ans -= mod;
	return ans;
}