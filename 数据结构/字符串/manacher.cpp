//以GYM 101981 M题为例，求以某位置i为右端的回文子串有多少个
int p[maxn << 1], tag[maxn << 1];//乘2的原因是manacher把原串拓展成二倍

void Manacher(char *s, int n) {//s从0开始
	int m = (n << 1) - 1, x = 0;
	char t[m + 5];
	memset(t, 0, sizeof t);

	for (int i = 0; i < n; i++) {
		t[i << 1] = s[i];
	}
	for (int i = 1; i < m; i++) {//p[i]为以i为中心、以真串字符为两端的最长回文半径,中间插'#'防止了偶数,但p[i]是加长串的半径
		if (i <= x + p[x]) {
			p[i] = min(p[(x << 1) - i], x + p[x] - i);
		}
		while (i - p[i] - 1 >= 0 && i + p[i] + 1 < m && t[i - p[i] - 1] == t[i + p[i] + 1]) {
			++p[i];
		}
		if (i + p[i] >= x + p[x]) {
			x = i;
		}
		//printf("%d\n", p[i]);
	}
	for (int i = 0; i < m; i++) {
		if (i - p[i] == 0 || i + p[i] == m - 1) {
			++p[i];
		}
	}
}

void Manacher(char *s, int n) {//s从1开始
	int m = (n << 1) - 1, x = 1;
	char t[m + 5];
	memset(t, '#', sizeof t);

	for (int i = 1; i <= n; i++) {
		t[(i << 1) - 1] = s[i];
	}
	for (int i = 2; i <= m; i++) {//p[i]为以i为中心、以真串字符为两端的最长回文半径,中间插'#'防止了偶数,但p[i]是加长串的半径
		if (i <= x + p[x]) {
			p[i] = min(p[(x << 1) - i], x + p[x] - i);
		}
		while (i - p[i] - 1 >= 1 && i + p[i] + 1 <= m && t[i - p[i] - 1] == t[i + p[i] + 1]) {
			++p[i];
		}
		if (i + p[i] >= x + p[x]) {
			x = i;
		}
	}
	for (int i = 1; i <= m; i++) {
		if (i - p[i] == 1 || i + p[i] == m) {
			++p[i];
		}
	}
}
