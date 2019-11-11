//计算从1～n中数字d出现过多少次，d属于[1, 9]
ll calc(ll n, int d) {
    ll res = 0, k = n;
    for (ll i = 1; k; i *= 10, k = n / i) {
        res += (k / 10) * i;
        int cur = k % 10;
        if (cur > d) res += i;
        else if (cur == d) res += n - k * i + 1;
    }
    return res;
}
