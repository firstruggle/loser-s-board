//HDU2586
const int maxn = 4e4 + 5;
int T, n, m;
int f[maxn], vis[maxn], dis[maxn], ans[maxn];
vector<P> vc[maxn];
vector<int> query[maxn], id[maxn];

inline int getf(int v) { return v == f[v] ? v : f[v] = getf(f[v]); }

inline void Tarjan(int cur) {
    vis[cur] = 1;

    for (auto son : vc[cur]) {
        if (vis[son.first])    continue;

        dis[son.first] = dis[cur] + son.second;
        Tarjan(son.first);
        f[son.first] = cur;
    }

    vis[cur] = 2;

    for (int i = 0; i < query[cur].size(); i++) {
        int v = query[cur][i], t = id[cur][i];

        if (vis[v] == 2) {
            int lca = getf(v);
            ans[t] = dis[cur] + dis[v] - 2 * dis[lca];
        }
    }
}

int main() {
    for (read(T); T; T--) {
        read(n), read(m);

        rep(i, 1, n) {
            vc[i].clear(), query[i].clear(), id[i].clear();
            f[i] = i, vis[i] = 0;
        }

        rep(i, 1, n - 1) {
            int u, v, cost;
            read(u), read(v), read(cost);
            vc[u].push_back({v, cost});
            vc[v].push_back({u, cost});
        }

        auto Add_Query = [](int u, int v, int i) {
            query[u].push_back(v);
            id[u].push_back(i);
        };

        rep(i, 1, m) {
            int u, v;
            read(u), read(v);
            Add_Query(u, v, i);
            if(u != v)    Add_Query(v, u, i);
        }

        Tarjan(1);

        rep(i, 1, m)
            writeln(ans[i]);
    }
    return 0;
}
