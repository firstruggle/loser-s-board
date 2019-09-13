int m, s[maxn], x[maxn], y[maxn], c[maxn]/*must maxn*/, sa[maxn], rk[maxn], height[maxn];
//sa[i]表示排名为i的后缀开头位置在哪， rk[i]表示开头位置是i的后缀排名第几
//height[i]表示第i名的后缀与第i-1名的后缀的最长公共前缀

void get_sa() {
	memset(c, 0, sizeof c);
	//c数组是桶, x[i]是第i个元素的第一关键字
	for (int i = 1; i <= n; i++) ++c[x[i] = s[i]];
	for (int i = 2; i <= m; i++) c[i] += c[i - 1];
	for (int i = n; i; i--) sa[c[x[i]]--] = i;

	for (int k = 1; k <= n; k <<= 1) {
		int num = 0;
		//y[i]表示第二关键字排名为i的数，第一关键字的位置
		//第n-k+1到第n位是没有第二关键字的 所以排名在最前面
		for (int i = n - k + 1; i <= n; i++) y[++num] = i;
		//排名为i的数 在数组中是否在第k位以后
		//如果满足(sa[i]>k) 那么它可以作为别人的第二关键字，就把它的第一关键字的位置添加进y就行了
		//所以i枚举的是第二关键字的排名，第二关键字靠前的先入队
		for (int i = 1; i <= n; i++) if (sa[i] > k) y[++num] = sa[i] - k;

		for (int i = 0; i <= m; i++) c[i] = 0;
		for (int i = 1; i <= n; i++) ++c[x[i]];
		for (int i = 2; i <= m; i++) c[i] += c[i - 1];
		for (int i = n; i; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;

		swap(x, y);
		x[sa[1]] = 1, num = 1;
		for (int i = 2; i <= n; i++)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
		if (num == n) break;
		m = num;
	}
	//height[i]: 第i名的后缀与第i-1名的后缀的lcp
	for (int i = 1; i <= n; i++) rk[sa[i]] = i;
	for (int i = 1, k = 0; i <= n; i++) {
		if (rk[i] == 1) {
			height[rk[i]] = 0;
			continue;
		}
		if (k) --k;
		int j = sa[rk[i] - 1];
		while (j + k <= n && i + k <= n && s[i + k] == s[j + k]) ++k;
		height[rk[i]] = k;
	}
}
