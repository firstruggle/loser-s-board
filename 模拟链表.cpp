struct list {
    int nxt[maxn], pre[maxn];

    void Init(int n) {
        rep(i, 1, n) {
            nxt[i] = i + 1;
            pre[i] = i - 1;
        }
    }

    void del(int x) {
        int t = pre[x], p = nxt[x];
        nxt[t] = p, pre[p] = t;
    }

    int Next(int x) { return nxt[x]; }
    int Last(int x) { return pre[x]; }
};
