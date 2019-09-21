//给定一堆点，求最大的凸包面积：凸包顶点由给点组成，凸包内不包含任何点。O（n^3）
const int maxn = 50 + 5;
const db eps = 1e-10;

int dcmp(db x) {
    if (fabs(x) <= eps) return 0;
    return x > 0 ? 1 : -1;
}

struct Point {
    db x, y;
    Point() {}
    Point(db x, db y):x(x), y(y) {}
};
#define V Point

V operator - (V A, V B) {
    return V(A.x - B.x, A.y - B.y);
}

bool operator == (V A, V B) {
    return dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) == 0;
}

db Cross(V A, V B) {
    return A.x * B.y - A.y * B.x;
}

db Dot(V A, V B) {
    return A.x * B.x + A.y * B.y;
}

int T, n, m;
db ans, dp[maxn][maxn];
V p[maxn], t[maxn];

bool cmp1(V A, V B) {
    if (A.x != B.x) return A.x < B.x;
    return A.y < B.y;
}

bool cmp2(V A, V B) {//极角排序，若在一条线上长度小的优先
    db s = Cross(A, B);
    if (dcmp(s) != 0) return dcmp(s) > 0;
    return dcmp(Dot(A, A) - Dot(B, B)) < 0;
}

bool in(int i, int j, int k) {//k在O，i，j组成的三角形内部
    return dcmp(Cross(t[k], t[i])) > 0 && dcmp(Cross(t[j], t[k])) > 0 && dcmp(Cross(t[i] - t[j], t[k] - t[j])) > 0;
}

void solve() {
    rep(i, 1, m) rep(j, 1, i - 1) dp[i][j] = 0;
    rep(i, 1, m) {
        rep(j, 1, i - 1) {
            if (dcmp(Cross(t[i], t[j])) == 0) continue;
            bool flag = 1;
            rep(k, j + 1, i - 1) {
                if (in(i, j, k)) {
                    flag = 0;
                    break;
                }
            }
            if (!flag) continue;

            db area = Cross(t[j], t[i]) / 2;
            dp[i][j] = area;
            if (j > 1 && dcmp(Cross(t[j - 1], t[j])) != 0) {//上一个点不在边上才可以拓展
                rep(k, 1, j - 1) {
                    if (!in(i, k, j))
                        dp[i][j] = max(dp[i][j], dp[j][k] + area);
                }
            }
            ans = max(ans, dp[i][j]);
        }
    }
}

int main() {
    //ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (scanf("%d", &T); T--; ) {
        scanf("%d", &n);
        rep(i, 1, n) scanf("%lf %lf", &p[i].x, &p[i].y);
        sort(p + 1, p + 1 + n, cmp1);
        ans = 0;
        rep(i, 1, n - 2) {//枚举凸壳最左边
            m = 0;
            rep(j, i + 1, n) {//坐标变换
                t[++m] = p[j] - p[i];
            }
            sort(t + 1, t + 1 + m, cmp2);
            solve();
        }
        printf("%.1lf\n", ans);
    }
}
