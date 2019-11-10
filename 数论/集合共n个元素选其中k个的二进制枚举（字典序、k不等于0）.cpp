void brute(int n, int k) {//一共n个选k个
	int comb = (1 << k) - 1;//第一个
	while (comb < (1 << n)) {
		int x = comb & -comb, y = comb + x;
		comb = ((comb & ~y) / x >> 1) | y;
	}
}
