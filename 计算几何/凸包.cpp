struct Point {
	db x, y;
	
	Point(){}

	Point(db a, db b):x(a), y(b){}

	bool operator < (const Point &rhs) const {
		if (dcmp(x - rhs.x) != 0)	return dcmp(x - rhs.x) < 0;
		return dcmp(y - rhs.y) < 0;
	}
}p[maxn];
Point v[maxn];

db Cross(Point A, Point B) {//顺时针转动则叉积为负
	return A.x * B.y - A.y * B.x;
}

Point operator - (Point A, Point B) {
	return Point(A.x - B.x, A.y - B.y);
}

bool operator == (Point A, Point B) {
	return dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) == 0;
}


void Convex(V *p, V *v, int n, int &cnt) {//标号以1开始的写法
    cnt = 0;
    sort(p + 1, p + n + 1, cmp1);
    n = unique(p + 1, p + n + 1) - p - 1;

	for (int i = 1; i <= n; i++) {
		while (cnt > 1 && Cross(v[cnt] - v[cnt - 1], p[i] - v[cnt - 1]) <= 0)	cnt--;
		v[++cnt] = p[i];
	}
	int k = cnt;
	for (int i = n - 1; i; --i) {
		while (cnt > k && Cross(v[cnt] - v[cnt - 1], p[i] - v[cnt - 1]) <= 0)	cnt--;
		v[++cnt] = p[i];
	}
	if (n > 1)	cnt--;
}


void ConvexHull(int n) {//标号以0开始
	cnt = 0;
	sort(p, p + n);
	n = unique(p, p + n) - p;//去重

	for (int i = 0; i < n; i++) {
		while (cnt > 1 && dcmp(Cross(v[cnt - 1] - v[cnt - 2], p[i] - v[cnt - 2])) <= 0)	cnt--;
		v[cnt++] = p[i];
	}
	int k = cnt;
	for (int i = n - 2; ~i; --i) {
		while (cnt > k && dcmp(Cross(v[cnt - 1] - v[cnt - 2], p[i] - v[cnt - 2])) <= 0)	cnt--;
		v[cnt++] = p[i];
	}
	if (n > 1)	cnt--;
}




---------------另一种写法-----------------
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

bool cmp2(V A, V B) {
    ll t = Cross(A, B);
    if (t) return t > 0;
    return Dot(A, A) < Dot(B, B);
}

int st[maxn];
void Convex(V *p, V *v, int n, int &cnt) {
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
