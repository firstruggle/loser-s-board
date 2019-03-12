//以BZOJ1101为例
//筛莫比乌斯函数
void pre(int n) {
	mu[1] = 1;
	rep(i, 2, n) {
		if (!vis[i]) {
			primes[++tot] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= tot && primes[j] * i <= n; j++) {
			vis[primes[j] * i] = true;
			if (i % primes[j] == 0)	break;
			mu[primes[j] * i] = - mu[i];
		}
	}
	rep(i, 1, n)	sum[i] = sum[i - 1] + mu[i];//预处理
}

ll solve(int n, int m) {
	if (n > m)	swap(n, m);
	ll ret = 0ll;
	for (int l = 1, r; l <= n; l = r + 1) {//整除分块
		r = min(n / (n / l), m / (m / l));
		ret += (ll)(sum[r] - sum[l - 1]) * (n / l) * (m / l);
	}
	return ret;
}

int main() {
	pre(maxn - 5);
	for (read(n); n; n--) {
		read(a), read(b), read(d);
		writeln(solve(a / d, b / d));
	}
	return 0;
}
