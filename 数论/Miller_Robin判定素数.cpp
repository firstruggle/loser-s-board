bool go(long long a, long long n)//核心算法
{
	long long r = n-1, j = 0;
	while (r&1 == 0)
	{
		r >>= 1;
		j++;
	}

	long long x = q_pow(a,r,n);//快速幂
	if (x == 1 || x == n-1)
		return true;
	while (j--)
	{
		x = q_mul(x,x,n);//快速乘
		if (x == n-1)
			return true;
	}
	return false;
}

bool miller_robin(long long n)
{
	if (n == 2)
		return true;
	if (n < 2 || n&1 == 0)
		return false;

	for (int i = 1; i <= 20; i++)//20次的错误率趋于0了
	{
		long long a = random(n-2)+1;//随机1~n-1的数
		if (!go(a,n))
			return false;
	}
	return true;
}