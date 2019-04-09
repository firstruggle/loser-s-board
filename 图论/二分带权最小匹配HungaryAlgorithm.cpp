//Codeforces 1107F
const int maxn = 505;
int n;
ll a, b, k, Matrix[maxn][maxn];

using T = ll;
T Hungary_Algorithm(int n, int m) {
    vector<T> u(n + 1), v(m + 1);
    vector<int> p(m + 1), way(m + 1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<T> minv(m + 1, INF);
        vector<char> used(m + 1, 0);
        do {
            used[j0] = 1;
            int i0 = p[j0], j1 = 0;
            T d = INF;
            for (int j = 1; j <= m; ++j)
                if (!used[j]) {
                    T cur = Matrix[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur, way[j] = j0;
                    if (minv[j] < d)
                        d = minv[j], j1 = j;
                }
            for (int j = 0; j <= m; ++j)
                if (used[j])
                    u[p[j]] += d, v[j] -= d;
                else
                    minv[j] -= d;
            j0 = j1;
        } while(p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    vector<int> ans(n + 1);
    for (int j = 1; j <= m; ++j)
        ans[p[j]] = j;
    T cost = -v[0];
    return cost;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    
    cin >> n;
    rep(i, 1, n) {
        cin >> a >> b >> k;
        rep(j, 1, n) {
        //Matrix表示第i种卡在距最后一天（j-1）天时借走能得到的钱数，本题需要最大费用故而取负
            Matrix[i][j] = min(0LL, -(a - b * min((ll)j - 1, k)));
        }
    }
    cout << -Hungary_Algorithm(n, n) << endl;
    return 0;
}
