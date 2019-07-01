/*以最简单的输入某数n，1～n之间不带4的数有多少个*/
/*再难一点的比如不要62，就要在搜索里面加pre之类的东西了。需要什么就往搜索里面加什么*/

int n;
int a[20], cnt, dp[20];

int solve(int pos, int limit) {
	if (!pos)	return 1;
	if (!limit && dp[pos])	return dp[pos];

	int ret = 0;
	int up = limit ? a[pos] : 9;
	for (int i = 0; i <= up; i++) {
		if (i == 4)	continue;//不要4
		ret += solve(pos - 1, limit & (i == a[pos]));
	}
	if (!limit)	dp[pos] = ret;
	return ret;
}

int main() {
	cin >> n;
	for (; n; n /= 10)
		a[++cnt] = n % 10;
	cout << solve(cnt, 1) - 1 << '\n';//去掉0
}
