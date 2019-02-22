//HDU2586 main code
const int maxn = 4e4 + 5;
int n, m, T, tot, t;
int head[maxn], d[maxn], dis[maxn], fa[maxn][20];
struct Edge {
	int to, cost, nxt;
}e[maxn << 1];

void add(int u, int v, int c) {
	e[++tot].to = v, e[tot].cost = c, e[tot].nxt = head[u], head[u] = tot;
}

void bfs() {
	queue<int> Q;
	Q.push(d[1] = 1);
	while (!Q.empty()) {
		int x = Q.front();
		Q.pop();
		for (int i = head[x]; i; i = e[i].nxt) {
			int y = e[i].to;
			if (d[y])	continue;
			d[y] = d[x] + 1;
			dis[y] = dis[x] + e[i].cost;
			fa[y][0] = x;
			rep(i, 1, t)
				fa[y][i] = fa[fa[y][i-1]][i-1];
			Q.push(y);
		}
	}
}

int LCA(int x, int y) {
	if (d[x] < d[y])	swap(x, y);
	irep(i, t, 0) {
		if (d[fa[x][i]] >= d[y]) {
			x = fa[x][i];
		}
	}
	if (x == y)	return x;

	irep(i, t, 0) {
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

int main() {
	for (T = ri; T; T--) {
		n = ri, m = ri;
		t = log(n) / log(2) + 1;
		tot = 0;
		rep(i, 1, n) {
			head[i] = d[i] = 0;
		}
		rep(i, 1, n - 1) {
			int u = ri, v = ri, c = ri;
			add(u, v, c);
			add(v, u, c);
		}
		bfs();
		while (m--) {
			int x = ri, y = ri;
			W(dis[x] + dis[y] - 2 * dis[LCA(x, y)]);
		}
	}
	return 0;
}
