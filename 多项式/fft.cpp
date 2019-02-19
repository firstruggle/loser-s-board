#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>
#define ri readint()
#define gc getchar()

int readint() {
	int x = 0, s = 1, c = gc;
	while (c <= 32)	c = gc;
	if (c == '-')	s = -1, c = gc;
	for (; isdigit(c); c = gc)	x = x * 10 + c - 48;
	return x * s;
}

const int maxn = 4 * 1e6 + 10;
const double PI = acos(-1.0);

struct Complex {
	double x, y;
	Complex(double a = 0, double b = 0):x(a), y(b){}
};
Complex operator + (Complex A, Complex B) { return Complex(A.x + B.x, A.y + B.y); }
Complex operator - (Complex A, Complex B) { return Complex(A.x - B.x, A.y - B.y); }
Complex operator * (Complex A, Complex B) { return Complex(A.x * B.x - A.y * B.y, A.x * B.y + A.y * B.x); }

Complex a[maxn], b[maxn];
int n, m;
int r[maxn], l, limit = 1;

void fft(Complex *A, int type) {
	for (int i = 0; i < limit; i++)
		if (i < r[i])
			std::swap(A[i], A[r[i]]);
	//迭代方式模拟递归写法，需要理解递归是怎么做的才能看懂这个
	for (int mid = 1; mid < limit; mid <<= 1) {
		//本来单位根是2*PI/len，这里len替换成2*mid，2就约掉了
		Complex Wn(cos(PI / mid), type * sin(PI / mid));
		for (int R = mid << 1, j = 0; j < limit; j += R) {
			Complex w(1, 0);//单位根的k次幂
			for (int k = 0; k < mid; k++, w = w * Wn) {
				//蝴蝶变换
				Complex x = A[j+k], y = w * A[j+k+mid];
				A[j+k] = x + y;
				A[j+k+mid] = x - y;
			}
		}
	}
}

int main() {
	n = ri, m = ri;
	for (int i = 0; i <= n; i++)
		a[i].x = ri;
	for (int i = 0; i <= m; i++)
		b[i].x = ri;

	while (limit <= n + m) {//长度变为2^l
		limit <<= 1;
		l++;
	}
	for (int i = 0; i < limit; i++)//二进制镜像
		r[i] = (r[i>>1] >> 1) | ((i&1) << (l-1));
	fft(a, 1);
	fft(b, 1);
	for (int i = 0; i < limit; i++)
		a[i] = a[i] * b[i];
	fft(a, -1);
	for (int i = 0; i <= n + m; i++)
		printf("%d ", (int)(a[i].x / limit + 0.5));
	return 0;
}