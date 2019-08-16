ll ksm(ll a, ll b, ll mod) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
	a = a * a % mod;
    }
    return res;
}
 
ll ksc(ll a, ll b, ll mod) {//注意这里a和b之前一定是要%mod的，才能保证a * b / mod不爆longlong
    return ((a * b - (ll)((long double)a / mod * b) * mod) % mod + mod) % mod;
}
bool go(ll a, ll n) {//核心算法
    ll r = n - 1, j = 0;
    while ((r & 1) == 0) {
        r >>= 1;
	j++;
    }

    ll x = ksm(a, r, n);//快速幂
    if (x == 1 || x == n - 1) return true;
    while (j--) {
	x = ksc(x, x, n);//快速乘
	if (x == n - 1)
	    return true;
    }    
    return false;
}

mt19937 rnd(time(0));
bool miller_robin(ll n) {
    if (n == 2) return true;
    if (n < 2 || (n & 1) == 0) return false;

    for (int i = 1; i <= 20; i++) {//20次的错误率趋于0了,10次不够
	ll a = rnd() % (n - 1) + 1;//随机1~n-1的数
	if (!go(a, n)) return false;
    }
    return true;
}
