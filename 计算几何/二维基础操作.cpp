struct Point
{
	double x, y;
	Point(double x = 0, double y = 0):x(x), y(y){}
};

typedef Point Vector;

int dcmp(double x)//比较
{
	const double eps = 1e-10;
	if (fabs(x) < eps)	return 0;
	else	return x < 0 ? -1 : 1;
}
Vector operator + (Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x * p, A.y * p); }
Vector operator / (Vector A, double p) { return Vector(A.x / p, A.y / p); }
bool operator < (const Point& A, const Point& B) { return A.x < B.x || (A.x == B.x && A.y < B. y); }
bool operator == (const Point& A, const Point& B) { return dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) == 0; }

const double PI = acos(-1.0);
double torad(double deg) { return deg/180 * PI; }//角度转弧度

double Dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; }//点积

double Length(Vector A) { return sqrt(Dot(A, A)); }//长度

double Angle(Vector A, Vector B) { return acos(Dot(A, B)/Length(A)/Length(B)); }//角度

Vector Rotate(Vector A, double rad) { return Vector(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.y*cos(rad)); }//逆时针旋转

double Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }//叉积

double Area2(Point A, Point B, Point C) { return Cross(B-A, C-A);}//二倍的三角形面积

Vector Normal(Vector A) { double L = Length(A); return Vector(-A.y/L, A.x/L); }//向量的单位法线，旋转的特殊情况

Vector Get_Line_Projection(Point P, Point A, Point B)//P在AB方向上的映射
{
 	Vector v = B - A;
  	return A + v*(Dot(v, P-A) / Dot(v, v));
}

Vector Get_Line_Intersect(Vector A, Vector v, Vector B, Vector w)//两直线交点
{
	Vector u = A - B;
	double t = Cross(w, u) / Cross(v, w);
	return A + v*t;
}

double Distance_to_Line(Point P, Point A, Point B)//点P到直线AB的距离
{
	Vector v1 = B - A, v2 = P - A;
	return fabs(Cross(v1, v2)) / Length(v1);
}

double Distance_to_Segment(Point P, Point A, Point B)//点P到线段AB的距离
{
	Vector v1 = B - A, v2 = P - A, v3 = P - B;
	if (A == B || dcmp(Dot(v1, v2)) < 0)	return Length(v2);//PA
	else if (dcmp(Dot(v1, v3)) > 0)	return Length(v3);//PB
	else	return fabs(Cross(v1, v2) / Length(v1));//PQ
}

bool On_Segment(Point P, Point A, Point B) { return dcmp(Cross(A - P, B - P)) == 0 && dcmp(Dot(A - P, B - P)) < 0; }//点在线段上

bool Segment_Proper_Intersection(Point a1, Point a2, Point b1, Point b2)//线段a1a2与b1b2相交（不包含端点）
{
	double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
	double c3 = Cross(b2 - b1, a1 - b1), c2 = Cross(b2 - b1, a2 - b1);
	return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}

double Polygon_Area(Point *p, int n)//多边形面积，逆时针取点0~n-1
{
	double area = 0;
	for (int i = 1; i < n-1; i++)
		area += Cross(p[i] - p[0], p[i+1] - p[0]);
	return area/2;
}

//基于复数的几何运算，效率不是很高
#include <complex>
typedef complex<double> Point;
typedef Point Vector;

double Dot(Vector A, Vector B) { return real(conj(A) * B); }// A（x+yi）的共轭（x-yi）乘以B，取实部
double Cross(Vector A, Vector B) { return imag(conj(A) * B); }//取虚部
Vector Rotate(Vector A, double rad) { return A * exp(Point(0, rad)); }//使用了欧拉公式：e^(0 + rad*i) = cos(rad) + sin(rad)*i，求完确实是旋转
