//就算初始各项都取了模也一样能搞
ll ksm(ll a, ll b) {
	ll res = 1;
	for (a %= mod; b; b >>= 1) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
	}
	return res;
}

namespace linear_seq {
	inline vector<ll> BM(vector<ll> x) {
	    vector<ll> ls, cur;
	    ll pn = 0, lf, ld;
	    for (int i = 0; i < x.size(); ++i) {
	        ll t = -x[i] % mod;
	        for (int j = 0; j < cur.size(); ++j)
	            t = (t + x[i - j - 1] * cur[j]) % mod;
	        if (!t) continue;
	        if (!cur.size()) {
	        	cur.resize(i + 1);
	        	lf = i;
	        	ld = t;
	        	continue;
	        }
	        ll k = -t * ksm(ld, mod - 2) % mod;
	        vector<ll> c(i - lf - 1);
	        c.push_back(-k);
	        for (int j = 0; j < ls.size(); ++j)
	        	c.push_back(ls[j] * k % mod);
	        if (c.size() < cur.size()) c.resize(cur.size());
	        for (int j = 0; j < cur.size(); ++j)
	            c[j] = (c[j] + cur[j]) % mod;
	        if (i - lf + ls.size() >= cur.size())
	            ls = cur, lf = i, ld = t;
	        cur = c;
	    }
	    vector<ll> &o = cur;
	    for(int i = 0; i < o.size(); ++i)
	        o[i] = (o[i] % mod + mod) % mod;
	    return o;
	}

	int N;
	//maxn比初始vector的size大即可
	ll a[maxn], h[maxn], t_[maxn], s[maxn], t[maxn];
	inline void mull(ll*p,ll*q) {
	    for (int i = 0; i < N + N; ++i) t_[i] = 0;
	    for (int i = 0; i < N; ++i) if(p[i])
	        for (int j = 0; j < N; ++j)
	            t_[i + j] = (t_[i + j] + p[i] * q[j]) % mod;
	    for (int i = N + N - 1; i >= N; --i) if(t_[i])
	        for (int j = N -1; ~j; --j)
	            t_[i - j - 1] = (t_[i - j - 1] + t_[i] * h[j]) % mod;
	    for (int i = 0; i < N; ++i) p[i] = t_[i];
	}
	inline ll calc(ll K) {
	    for (int i = N; ~i; --i)
	    	s[i] = t[i] = 0;
	    s[0] = 1;
	    if (N != 1) t[1] = 1;
	    else t[0] = h[0];
	    for (; K; mull(t, t), K >>= 1)
	    	if (K & 1) mull(s, t);
	    ll su = 0;
	    for (int i = 0; i < N; ++i)
	    	su = (su + s[i] * a[i]) % mod;
	    return (su % mod + mod) % mod;
	}
	inline ll get(vector<ll> x, ll n) {
	    if (n < x.size()) return x[n];
	    vector<ll> v = BM(x);
	    N = v.size();
	    if (!N) return 0;
	    for(int i = 0; i < N; ++i)
	    	h[i] = v[i], a[i] = x[i];
	    return calc(n);
	}
}

int main() {
	vector<ll> a;
	a.push_back(1);
	a.push_back(1);
	//a[0] = 1, a[1] = 1
	rep(i, 2, 10) {//
		a.push_back(a[i - 1] + a[i - 2]);
	}
	rep(i, 3, 10000) {
		//注意第二个参数代表vector中的第几个，也就是事实上的第n+1项，故而扔进去n-1
		cout << linear_seq::get(a, i - 1) << endl;
		//a[2] = 2, a[3] = 3, a[4] = 5 
	}
}
