int cmp(const int i, const int j)	{	return w[i]<w[j];	}
int find(int v)	{	return f[v] == v ? v : f[v] = find(f[v]);	}
int kruskal()
{
	int ans = 0;
	for (int i = 0; i < n; i++)	f[i] = i;
	for (int i = 0; i < m; i++)	r[i] = i;
	
	sort(r, r+m, cmp);
	
	for (int i = 0; i < m; i++)
	{
		int e = r[i];
		int x = find(u[e]), y = find(v[e]);
		if (x != y)	ans += w[e], p[x] = y;
	}

	return ans;
}