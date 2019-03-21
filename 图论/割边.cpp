void dfs(int cur, int fa) {
    //dfn是时间戳，low是此点能到达的最早的点
    DFN[cur] = low[cur] = ++time;
    vis[cur] = true;
    for (int i = head[cur]; i; i = e[i].nxt) {
        int son = e[i].to;
        if (!vis[son]) {
            dfs(son, cur);
            low[cur] = min(low[cur], low[son]);
            if (low[son] > DFN[cur])//如果孩子能到达的地方比父亲晚说明这是割边
                ans++;//ans是割边的个数
        } else if (son != fa) {
            low[cur] = min(low[cur], DFN[son]);
        }
    }
}
