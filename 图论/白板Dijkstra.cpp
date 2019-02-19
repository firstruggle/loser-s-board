memset(done, false, sizeof(done));
for (int i = 0; i < n; i++)	d[i] = INF;
d[s] = 0;

for (int i = 0; i < n; i++)
{
	int x, m = INF;
	for (int j = 0; j < n; j++)	
		if (!done[j] && d[j] <= m)
			m = d[x = j];

	done[x] = true;
	for (int j = 0; j < n; j++)
		d[j] = min(d[j], d[x]+w[x][j]);
}