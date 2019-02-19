int n, m;
int first[maxn];
int u[maxm], v[maxm], w[maxm], next[maxm];

void read_graph()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)	first[i] = -1;

	for (int e = 0; e < m; e++)
	{
		scanf("%d%d%d", &u[e], &v[e], &w[e]);
		next[e] = first[u[e]];
		first[u[e]] = e;
	}
}