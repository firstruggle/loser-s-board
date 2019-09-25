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
