//求解a ^ x = b (% p)中最小非负x值
//map常数大可能会被卡，手写散列表
int hash_table[maxm], val[maxm];
//memset(hash_table, -1, sizeof(hash_table));

int ksm(int a, int b, int mod) {
	int res = 1;
	for (; b; b >>= 1) {
		if (b & 1)	res = (ll)res * a % mod;
		a = (ll)a * a % mod;
	}
	return res;
}

int find(int n) {
	int id = n % maxm;
	while (hash_table[id] >= 0 && hash_table[id] != n)
		id = (id + 1) % maxm;
	return id;
}

int BSGS(int a, int b, int p) {
	if (p == 1)	return 0;
	a %= p, b %= p;
	if (!a)	return b ? -1 : 1;

	int m = sqrt(p) + 1;
	int now = b;
	hash_table[now % maxm] = now;
	val[now % maxm] = 0;
	for (int i = 1; i <= m; i++) {
		now = (ll)now * a % p;
		int pos = find(now);
		hash_table[pos] = now;
		val[pos] = i;
	}

	int t = ksm(a, m, p);
	now = 1;
	for (int i = 1; i <= m; i++) {
		now = (ll)now * t % p;
		int pos = find(now);
		if (hash_table[pos] >= 0) {
			return i * m - val[pos];
		}
	}
	return -1;
}



----------------EXBSGS-----------------
//后半部分和拔山盖世是一样的，只是前面多加了一些话
int EXBSGS(int a, int b, int p) {
	if (p == 1)	return 0;
	a %= p, b %= p;
	if (!a)	return b ? -1 : 1;
//扩展部分开始
	int k = 0, tmp = 1, d;
	while (true) {
		d = __gcd(a, p);
		if (d == 1)
			break;
		if (b % d)
			return -1;
		b /= d, p /= d;
		tmp = (ll)tmp * (a / d) % p;
		k++;
		if (tmp == b)
			return k;
	}
//扩展部分结束
	memset(hash_table, -1, sizeof(hash_table));
	int m = sqrt(p) + 1;
	int now = b;
	hash_table[now % maxc] = now;
	val[now % maxc] = 0;
	for (int i = 1; i <= m; i++) {
		now = (ll)now * a % p;
		int pos = find(now);
		hash_table[pos] = now;
		val[pos] = i;
	}

	now = ksm(a, m, p) % p;
	for (int i = 1; i <= m; i++) {
		tmp = (ll)tmp * now % p;
		int pos = find(tmp);
		if (hash_table[pos] >= 0)
			return i * m - val[pos] + k;//返回值多了k
	}
	return -1;
}