bool dfs(int x) {
    for (int i = 1; i <= n; i++)//正常应该是枚举边，此处为邻接矩阵
        if (!vis[i] && a[x][i]) {
            vis[i] = 1;
            if (!match[i] || dfs(match[i])) {
                match[i] = x; return 1;
            }
        }
    return 0;
}

bool Solve() {
    memset(match, 0, sizeof match);
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof vis);
        if (!dfs(i))   return 0;
    }
    return 1;
}
