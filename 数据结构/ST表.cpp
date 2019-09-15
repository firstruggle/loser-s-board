int rmq(int i, int j) {
    if (i > j) swap(i, j);
    int k = 0;
    while (i + (1 << (k + 1)) <= j) k++;
    return min(st[i][k], st[j - (1 << k) + 1][k]);
}

void get_ST() {
    for (int i = 1; i <= n; i++)
	st[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
	for (int i = 1; i + (1 << j) - 1 <= n; i++)
	    st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}
