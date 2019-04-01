inline void bfs() {
	queue<int> Q;
	Q.push(1), d[1] = 1;

	while (!Q.empty()) {
		int x = Q.front(); Q.pop();

		for (int i = head[x]; i; i = nxt[i]) {
			int y = to[i];
			if (d[y])	continue;

			d[y] = d[x] + 1;
			dis[y][0] = val[i];
			f[y][0] = x;

			rep(j, 1, t) {
				f[y][j] = f[f[y][j - 1]][j - 1];
				dis[y][j] = dis[f[y][j - 1]][j - 1] + dis[y][j - 1];
			}

			Q.push(y);
		}
	}
}

inline ll lca(int x, int y) {
	ll ret = 0;

	if (d[x] > d[y])	swap(x, y);

	irep(i, t, 0)
		if (d[f[y][i]] >= d[x]) {
			ret += dis[y][i];
			y = f[y][i];
		}

	if (x == y)	return ret;

	irep(i, t, 0)
		if (f[x][i] != f[y][i]) {
			ret += dis[x][i] + dis[y][i];
			x = f[x][i], y = f[y][i];
		}

	return ret + dis[x][0] + dis[y][0];
}
