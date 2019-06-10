int n, m, Cost[maxn];
int f[maxn][maxn], size[maxn];
vector<pair<int, int>> adj[maxn];

void dfs(int u) {
	if (u > n - m) {//叶子
		size[u] = 1;
		f[u][1] = Cost[u];
	}
	f[u][0] = 0;
	for (auto son : adj[u]) {
		int v = son.first, c = son.second;
		dfs(v);
		size[u] += size[v];
		for (int j = size[u]; j; j--) {//必须倒序，背包其实省略了一维[i]
			for (int k = 0; k <= min(j, size[v]); k++) {//当前子树选几个
				f[u][j] = max(f[u][j], f[v][k] + f[u][j - k] - c);
			}
		}
	}
}
