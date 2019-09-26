//洛谷4557(jsoi2018）
const int maxn = 1e5 + 5;

int n, m, q, tot1, tot2, tot, cnt;

struct Point {
    ll x, y;
    Point() {}
    Point(ll x, ll y):x(x), y(y) {}
};
typedef Point V;

V operator - (V A, V B) {
    return V(A.x - B.x, A.y - B.y);
}

V operator + (V A, V B) {
    return V(A.x + B.x, A.y + B.y);
}

bool operator == (V A, V B) {
    return A.x == B.x && A.y == B.y;
}

ll Dot(V A, V B) {
    return A.x * B.x + A.y * B.y;
}

ll Cross(V A, V B) {
    return A.x * B.y - A.y * B.x;
}

bool cmp1(V A, V B) {
    if (A.x != B.x) return A.x < B.x;
    return A.y < B.y;
}

bool cmp2(V A, V B) {//极角排序
    ll t = Cross(A, B);
    if (t) return t > 0;
    return Dot(A, A) < Dot(B, B);
}

V A[maxn << 1], A1[maxn], A2[maxn], v[maxn], v1[maxn], v2[maxn], s1[maxn], s2[maxn];

int st[maxn];
void Convex(V *p, V *v, int n, int &cnt) {//一种凸包写法
    rep(i, 1, n) v[i] = p[i];
    sort(v + 1, v + 1 + n, cmp1);
    V Base = v[1];
    st[++cnt] = 1;
    rep(i, 1, n) v[i] = v[i] - Base;
    sort(v + 2, v + 1 + n, cmp2);
    rep(i, 2, n) {
        while (cnt > 1 && Cross(v[i] - v[st[cnt - 1]], v[st[cnt]] - v[st[cnt - 1]]) >= 0) cnt--;
        st[++cnt] = i;
    }
    rep(i, 1, cnt) v[i] = v[st[i]] + Base;
}

void Minkowski() {//类似归并排序，求出的点还是凸包
    rep(i, 1, tot1) s1[i] = v1[i % tot1 + 1] - v1[i];
    rep(i, 1, tot2) s2[i] = v2[i % tot2 + 1] - v2[i];
    A[tot = 1] = v1[1] + v2[1];
    int p1 = 1, p2 = 1;
    while (p1 <= tot1 && p2 <= tot2) {
        ++tot;
        A[tot] = A[tot - 1] + (Cross(s1[p1], s2[p2]) >= 0 ? s1[p1++] : s2[p2++]); 
    }
    while (p1 <= tot1) {
        ++tot;
        A[tot] = A[tot - 1] + s1[p1++];
    }
    while (p2 <= tot2) {
        ++tot;
        A[tot] = A[tot - 1] + s2[p2++];
    }
}

int In(V w) {//判断某向量是否在以原点为左下的凸包内
    int pos = lower_bound(v + 2, v + 1 + cnt, w, cmp2) - v - 1;
    return Cross(w - v[pos], v[pos % cnt + 1] - v[pos]) <= 0;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> q;
    rep(i, 1, n) cin >> A1[i].x >> A1[i].y;
    rep(i, 1, m) {//这里b集合取反是根据题意
        cin >> A2[i].x >> A2[i].y;
        A2[i].x = -A2[i].x;
        A2[i].y = -A2[i].y;
    }
    Convex(A1, v1, n, tot1);
    Convex(A2, v2, m, tot2);
    Minkowski();//两个凸包的闵可夫斯基和
    Convex(A, v, tot, cnt);
    V base = v[1];
    rep(i, 1, cnt) v[i] = v[i] - base;
    while (q--) {
        ll x, y;
        cin >> x >> y;
        cout << In(V(x, y) - base) << '\n';
    }
}
