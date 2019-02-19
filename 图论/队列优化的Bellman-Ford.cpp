bool bellmanford(int s)
{
	vector <pair<int,int> > v[maxn];
	queue <int> Q;

	memset(vis, false, sizeof(vis));
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; i++)	d[i] = INF;
	d[s] = 0;
	vis[s] = true;
	Q.push(s);

	while (!Q.empty())
	{
		int u = Q.front();Q.pop();
		vis[u] = false;
		for (auto i : v[u])
			if (d[u] < INF && d[i.first] > d[u] + i.second)
			{
				d[i.first] = d[u] + i.second;
				if (!vis[i.first])
				{
					Q.push(i.first);
					vis[i.first] = true;
					if (++cnt[i.first] > n)	return false;//判负环
				}
			}
	}
}