int block[M], L[sqrt(M)], R[sqrt(M)];
int mp[sqrt(M)][N];//对于每一块中的某个点的值进行记录想要的值

void build(int m) {
    int t = sqrt(m), tot = (m + t - 1) / t;
    for (int i = 1; i <= m; i++) {
        block[i] = (i + t - 1) / t;
    }
    for (int i = 1; i <= tot; i++) {
        L[i] = (i - 1) * t + 1, R[i] = i * t;
        for (int j = 1; j <= n; j++)
            mp[i][j] = 0;
    }
    for (int i = 1; i <= m; i++) {//mp使用实例：边分块，点记录值
        scanf("%d %d", &u, &v);
        mp[block[i]][u] ^= hs[v];
        mp[block[i]][v] ^= hs[u];
        edge[i] = {u, v};
    }
}

void query(int u, int v) {
    int l = block[u], r = block[v];
    if (l == r) {//在一个块里面直接暴力
        Act(u, v);
    } else {//分别块内暴力，其余块打标记
        Act(u, R[l]), Act(L[r], v);
        for (int i = l + 1; i < r; i++)
            //...自行打标记
    }
}
