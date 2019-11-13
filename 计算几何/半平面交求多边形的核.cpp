
const int maxn = 1e3;
const double EPS = 1e-9;

int T, n;
typedef struct Grid {
    double x, y;
    Grid(double a = 0, double b = 0) {x = a, y = b;}
} Point, Vector;

Vector operator - (Point a, Point b) {return Vector(b.x - a.x, b.y - a.y);}
double operator ^ (Vector a, Vector b) {return a.x * b.y - a.y * b.x;}//叉乘

struct Line {
    Point s, e;
    Line() {}
    Line(Point a, Point b) {s = a, e = b;}
};
Point p[maxn];
Line L[maxn], que[maxn];

//得到极角角度
double getAngle(Vector a) {
    return atan2(a.y, a.x);
}

//得到极角角度
double getAngle(Line a) {
    return atan2(a.e.y - a.s.y, a.e.x - a.s.x);
}

//排序：极角小的排前面，极角相同时，最左边的排在最后面，以便去重，这是必需步骤
bool cmp(Line a, Line b) {
    Vector va = a.e - a.s, vb = b.e - b.s;
    double A =  getAngle(va), B = getAngle(vb);
    if (fabs(A - B) < EPS) return ((va) ^ (b.e - a.s)) >= 0;
    return A < B;
}

//得到两直线相交的交点
Point getIntersectPoint(Line a, Line b) {
    double a1 = a.s.y - a.e.y, b1 = a.e.x - a.s.x, c1 = a.s.x * a.e.y - a.e.x * a.s.y;
    double a2 = b.s.y - b.e.y, b2 = b.e.x - b.s.x, c2 = b.s.x * b.e.y - b.e.x * b.s.y;
    return Point((c1*b2-c2*b1)/(a2*b1-a1*b2), (a2*c1-a1*c2)/(a1*b2-a2*b1));
}

//判断 b,c 的交点是否在 a 的右边
bool onRight(Line a, Line b, Line c) {
    Point o = getIntersectPoint(b, c);
    if (((a.e - a.s) ^ (o - a.s)) < 0) return true;
    return false;
}

bool HalfPlaneIntersection() {
    sort(L, L + n, cmp);//排序
    int head = 0, tail = 0, cnt = 0;//模拟双端队列

    for (int i = 0; i < n - 1; i++) {
        if (fabs(getAngle(L[i]) - getAngle(L[i + 1])) < EPS) {
            continue;
        }
        L[cnt++] = L[i];
    }
    L[cnt++] = L[n - 1];

    for (int i = 0; i < cnt; i++) {
        //判断新加入直线产生的影响
        while(tail - head > 1 && onRight(L[i], que[tail - 1], que[tail - 2])) tail--;
        while(tail - head > 1 && onRight(L[i], que[head], que[head + 1])) head++;
        que[tail++] = L[i];
    }
    //最后判断最先加入的直线和最后的直线的影响
    while(tail - head > 1 && onRight(que[head], que[tail - 1], que[tail - 2])) tail--;
    while(tail - head > 1 && onRight(que[tail - 1], que[head], que[head + 1])) head++;
    if (tail - head < 3) return false;
    return true;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {//顺时针输入点
            scanf("%lf %lf", &p[i].x, &p[i].y);
        }
        //半平面交的组成外多边形的向量需要逆时针的指向
        for (int i = 0; i < n; i++) {//p[i + 1]指向p[i]
            L[i] = Line(p[(i + 1)%n], p[i]);
        }

        if (HalfPlaneIntersection()) printf("YES\n");
        else printf("NO\n");
  }
  return 0;
}
