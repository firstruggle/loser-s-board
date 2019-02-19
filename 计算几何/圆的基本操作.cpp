struct Circle
{
	Point c;
	double r;
	// Circle(Point a = (0, 0), double x = 0):c(a), r(x){}
	Point point(double seta) { return Point(c.x + cos(seta)*r, c.y + sin(seta)*r); }//已知角度求圆上某点
};

struct Line
{
	Point p;
	Vector v;
	Line(Point p, Vector v):p(p), v(v) { }

	Point point(double t) { return p + v*t; }//已知参数t求直线上一点
	Line move(double d) { return Line(p + Normal(v)*d, v); }//平移
};

int get_Tangents(Point P, Circle C, vector<Vector> &v)//过定点做圆的切线
{
	Vector u = C.c - P;
	double d = Length(u);

	if (dcmp(d - C.r) < 0)	return 0;//点在圆内部
	else if (dcmp(d - C.r) == 0)//点在圆上
	{
		v.push_back(Rotate(u, PI/2));
		return 1;
	}
	else//两条切线
	{
		double a = asin(C.r / d);
		v.push_back(Rotate(u, a));
		v.push_back(Rotate(u, -a));
		return 2;
	}
}

int get_Line_Circle_Intersection(Line L, Circle C, vector<Point> &ans)//方程求解直线与圆的交点
{
	double t1, t2;
	double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;
	double e = a*a + c*c, f = 2*(a*b + c*d), g = b*b + d*d - C.r*C.r;
	double delta = f*f - 4*e*g;//判别式
	
	if (dcmp(delta) < 0)	return 0;//相离
	else if (dcmp(delta) == 0)//相切
	{
		t1 = t2 = -f/2/e;
		ans.push_back(L.point(t1));
		return 1;
	}
	else//相交
	{
		t1 = (-f + sqrt(delta)) / 2 / e;
		t2 = (-f - sqrt(delta)) / 2 / e;
		ans.push_back(L.point(t1)), ans.push_back(L.point(t2));
		return 2;
	}
}

inline double angle(Vector A) { return atan2(A.y, A.x); }//某向量极角

int get_Circle_Circle_Intersection(Circle C1, Circle C2, vector<Point> &v)//圆与圆的交点
{
	double d = Length(C1.c - C2.c);
	if (dcmp(d) == 0)
	{
		if (dcmp(C1.r - C2.r) == 0)	return -1;//重合
		return 0;//同心
	}
	if (dcmp(C1.r + C2.r - d) < 0)	return 0;//外离
	if (dcmp(fabs(C1.r - C2.r) - d) > 0)	return 0;//内含

	double a = angle(C2.c - C1.c);//注意这里先后顺序
	double da = acos((C1.r*C1.r + d*d - C2.r*C2.r) / (2*C1.r*d));//余弦公式
	Point p1 = C1.point(a - da), p2 = C1.point(a + da);

	v.push_back(p1);
	if (p1 == p2)	return 1;
	v.push_back(p2);
	return 2;
}

//两圆的公切线，-1表示无数条
//a[i]和b[i]分别是第i条切线在圆A和圆B上的切点
//这板子有些奇怪，以后用上再更
int get_Common_Tangents(Circle A, Circle B, Point *a, Point *b)
{
	int cnt = 0;
	if (A.r < B.r)	{ swap(A, B), swap(a, b); }
	double d2 = (A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y);
	if (d2 == 0 && A.r == B.r)	return -1;//同一个圆

	double rdiff = A.r - B.r;
	double rsum = A.r + B.r;
	double base = atan2(B.y - A.y, B.x - A.x);

	if (d2 < rdiff * rdiff)	return 0;//内含
	if (d2 == rdiff*rdiff)	
	{
		a[cnt] = 
	}
	
	
}