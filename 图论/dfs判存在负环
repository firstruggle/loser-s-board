db dis[maxn];
bool vis[maxn];

bool dfs(int cur) {//注意此题为有向图
	vis[cur] = 1;
	for (auto i : adj[cur])
		if (dis[i.fi] > dis[cur] + i.se - mid) {
			dis[i.fi] = dis[cur] + i.se - mid;
			if (vis[i.fi] || dfs(i.fi))
				return vis[cur] = 0, 1;
		}
	return vis[cur] = 0;
}

bool check() {
	memset(dis, 0, sizeof dis);
	for (int i = 1; i <= n; i++)
		if (dfs(i))	
			return 1;
	return 0;
}
