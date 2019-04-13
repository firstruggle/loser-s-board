namespace EXGCD {
	int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

	ll exgcd(ll a, ll b, ll &x, ll &y) {
		if (!b) {
			x = 1, y = 0;
			return a;
		}
		ll q = exgcd(b, a % b, y, x);
		y -= a / b * x;
		return q;
	}

	int solve(int a, int b, int c) {//ax = c (% b)求x的解
		if (!c)	return 0;
		int q = gcd(a, b);
		if (c % q)	return -1;

		a /= q, b /= q, c /= q;
		ll ans, __;
		exgcd((ll)a, (ll)b, ans, __);
		ans = (ans * c % b + b) % b;
		return ans;
	}
}
