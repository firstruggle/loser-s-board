//期望复杂度为：根号根号n
long long pollard_rho(long long p, long long c)
{
	long long i=1 , k=2 , x=random(p-1)+1/*随机1~p的数*/;
	long long y=x , d;

	while (true)
	{
		i++;
		x = (q_mul(x,x,p) + c) % p;//快速乘
		d = gcd(y-x , p);
		if (d > 1 && d < p)//找到
			return d;
		if (y == x)//循环了没找到
			return p;
		if (i == k)//优化功能
			y = x,k <<= 1;
	}
}

void find(long long n, long long c)//c为任意写的一个常数
{
	if (n == 1)	return;
	if (n是素数)
	{
		insert(n);/*视需求写*/
		return；
	}

	long long p = n;
	while (p >= n)//直到随机到它的因数
		p = pollard_rho(p,c--);
	find(p,c);
	find(n/p,c);
}