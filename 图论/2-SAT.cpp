struct TWO_SAT {
    int n;
    vector<int> G[maxn * 2];
    bool mark[maxn * 2];
    int record[maxn * 2], t;

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n * 2; i++)	G[i].clear();
        memset(mark, false, sizeof(mark));
    }

    bool dfs(int u) {
        if (mark[u ^ 1]) return false;
        if (mark[u]) return true;

        mark[u] = true;
        record[t++] = u;
        for (int i : G[u]) if (!dfs(i)) return false;
        return true;
    }

    void add(int x, int xval, int y, int yval) {//x选择xval时y必须选择yval
        x = x * 2 + xval;
        y = y * 2 + yval;
        G[x].push_back(y);
    }

    bool solve() {//是否有方案
        for (int i = 0; i < n * 2; i += 2)
            if (!mark[i] && !mark[i + 1]) {
                t = 0;
                if (!dfs(i)) {
                    while (t) mark[record[--t]] = false;
                    if (!dfs(i + 1)) return false;
                }
            }
        return true;
    }

    bool value(int i) {//具体方案，i为0～n - 1，代表第i个变量是否选择为真
        return mark[i * 2 + 1];
    }
}sat;
