void pre(int  n) {
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
int v[MAX_N], prime[MAX_N], n, m;

void pre(int n) {
	memset(v, 0, sizeof(v));
	int m = 0;

	rep(i, 2, n) {
		if (!v[i]) {
			primes[++m] = i;
			v[i] = i;
		}
		for (int j = 1; j <= m && primes[j] <= n / i; j++) {
			if (primes[j] > v[i]) break;
			v[i * primes[j]] = primes[j];
		}
	}
	//prime里存放的为素数
}
