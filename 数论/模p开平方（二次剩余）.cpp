int a, w;
struct field {//扩域 x实部 y虚部
    ll x, y;
    field() {}
    field(ll a, ll b):x(a), y(b) {}
};
field operator * (field a, field b) {
	return field((a.x * b.x % mod + a.y * b.y % mod * w % mod) % mod, (a.x * b.y % mod + a.y * b.x % mod) % mod);
}
  
ll ksm(ll a, ll b, ll res = 1) {
	for (; b; b >>= 1) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
	}
	return res;
}
  
field powfield(field a, ll b) {//扩域快速幂
    field res = field(1, 0);
    for (; b; b >>= 1) {
    	if (b & 1) res = res * a;
    	a = a * a;
    }
    return res;
}
  
int legander(int x) {
//勒让德记号
//返回-1时x不为二次剩余
//返回1时x为二次剩余
//返回0时p整除x
    ll a = ksm(x, (mod - 1) / 2);
    if (a + 1 == mod) return -1;
    return a;
}

mt19937 rnd(time(0));
int surplus(int x){
//求b.x*b.x==a(% 奇素数mod)时的b.x
//即给定a，求a为二次剩余时的解b.x
//a为非二次剩余时返回-1 while(1)期望次数两次
    if (x == 0) return 0;
    if (legander(x) == -1) return -1;
    while (1) {
        a = rnd() % mod;
        w = (((ll)a * a - x) % mod + mod) % mod;
        if (legander(w) == -1) break;
    }
    field b = field(a, 1);
    b = powfield(b, (mod + 1) / 2);
    return b.x;
}
