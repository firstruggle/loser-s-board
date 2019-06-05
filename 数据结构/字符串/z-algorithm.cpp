//z[i]表示“此位开始的子串”与“原串”的最大公共前缀
void Z_algorithm(char *s, int n) {//s从0开始
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i > r) {
			l = i, r = i;
			while (r < n && s[r - l] == s[r])	r++;
			z[i] = r - l; r--;
		} else {
			int k = i - l;
			if (z[k] < r - i + 1)	z[i] = z[k];
			else {
				l = i;
				while (r < n && s[r - l] == s[r])	r++;
				z[i] = r - l; r--;
			}
		}
	}
}

void Z_algorithm(char *s, int n) {//s从1开始
	int l = 1, r = 1;
	for (int i = 2; i <= n; i++) {
		if (i > r) {
			l = i, r = i;
			while (r <= n && s[r - l + 1] == s[r])	r++;
			z[i] = r - l; r--;
		} else {
			int k = i - l + 1;
			if (z[k] < r - i + 1)	z[i] = z[k];
			else {
				l = i;
				while (r <= n && s[r - l + 1] == s[r])	r++;
				z[i] = r - l; r--;
			}
		}
	}
}
