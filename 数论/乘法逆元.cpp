//注意：只有两数互素，才有乘法逆元
//O(logn)求单个数(1/a)%p的乘法逆元
//法1：若p为素数，快速幂求ksm(a, p-2, p)
//法2：若a和p互质，快速幂求ksm(a, φ(p)-1, p)
//法3：exgcd，代码如下
ll inv(ll a, ll p) {
	ll d, x, y;
	exgcd(a, p, d, x, y);
	return d == 1 ? (x + p) % p : -1;
}

//O(n)求区间内所有数的逆元
void getinv(int n) {
	inv[1] = 1;
	for (int i = 2; i <= n; i++) {
		inv[i] = mod - (ll)mod / i * inv[mod % i] % mod;
		//或者：
		//inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
	}
}

//组合计算时求1~n中i！的逆元
void facinv(int n) {
	fac[0] = inv[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = (ll)fac[i - 1] * i % p;

	inv[n] = ksm(fac[n], p - 2, p);
	for (int i = n - 1; i; i--)
		inv[i] = (ll)(inv[i+1] * (i+1)) % p;
	//1 / i! == 1 / (i+1)! * (i+1)
}
