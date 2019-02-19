#include <bits/stdc++.h>
#define ll long long
#define ri readll()
#define gc getchar()
#define rep(i, a, b) for (int i = a; i <= b; i++)
using namespace std;

const int P = 998244353, G = 3, Gi = 332748118, maxn = 4 * 1e6 + 5;
//P的原根为3,3%P的逆元为332748118
//原根意味着：3^(P-1) % P = 1,其中P-1是3%P的阶，本应是φ(P)，这里恰好为大素数
ll n, m;
ll a[maxn], b[maxn];
int limit = 1, l, r[maxn];

ll readll() {
	ll x = 0ll, s = 1ll;
	char c = gc;
	while (c <= 32)	c = gc;
	if (c == '-')	s = -1ll, c = gc;
	for (; isdigit(c); c = gc)	x = x * 10 + c - 48;
	return x * s;
}

ll ksm(ll a, ll b, int mod) {
	ll res = 1ll;
	for (; b; b >>= 1) {
		if (b & 1)	res = res * a % mod;
		a = a * a % mod;
	}
	return res;
}

void NTT(ll *A, int flag) {
	rep(i, 0, limit)
	if (i < r[i])
		swap(A[i], A[r[i]]);

	for (int mid = 1; mid < limit; mid <<= 1) {
		//如果是变换则单位根为3^[(P-1)/(len)] % P,逆变换则用逆元
		ll Wn = ksm(flag ? G : Gi, (P-1) / (mid*2), P);
		for (int R = mid << 1, j = 0; j < limit; j += R) {
			ll w = 1ll;
			for (int k = 0; k < mid; k++, w = w * Wn % P) {
				ll x = A[j+k], y = A[j+k+mid] * w % P;
				A[j+k] = (x + y) % P;
				A[j+k+mid] = (x - y + P) % P;
			}
		}
	}
}

int main() {
	n = ri, m = ri;
	rep(i, 0, n)	a[i] = (ri + P) % P;
	rep(i, 0, m)	b[i] = (ri + P) % P;

	while (limit < n + m + 1) {
		limit <<= 1;
		l++;
	}
	rep(i, 0, limit)	r[i] = (r[i>>1] >> 1) | ((i & 1) << (l - 1));
	NTT(a, 1);	NTT(b, 1);
	rep(i, 0, limit)	a[i] = a[i] * b[i] % P;
	NTT(a, 0);

	ll inv = ksm(limit, P - 2, P);//最后变换回来要乘长度的逆元
	rep(i, 0, n + m)	printf("%lld ", a[i] * inv % P);

	return 0;
}