for (int i = 0; i < n; i++)	d[i] = INF;
d[s] = 0;

for (int k = 0; k < n-1; k++)//迭代n-1次
	for (int i = 0; i < m; i++)//检查每条边
	{
		int x = u[i], y = v[i];
		if (d[x] < INF)
			d[y] = min(d[y], d[x]+w[i]);
	}