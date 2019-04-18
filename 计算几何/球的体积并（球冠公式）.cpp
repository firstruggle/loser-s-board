#include <bits/stdc++.h>
using namespace std;

typedef double db;
const db eps = 1e-8;
const db PI = acos(-1.0);

int dcmp(db x) {
    if (fabs(x) < eps)    return 0;
    return x > 0 ? 1 : -1;
}

db sqr(db x) { return x * x; }

struct Sphere {
    db x, y, z, r;
    
    db V() {
        return PI * r * r * r * 4 / 3;
    }
    
    db Crown(db h) {//球冠体积公式
        return PI * sqr(h) * (3 * r - h) / 3;
    }
}A, B;

db dis(Sphere A, Sphere B) {
    db t = sqr(A.x - B.x) + sqr(A.y - B.y) + sqr(A.z - B.z);
    return sqrt(t);
}

db solve() {
    db d = dis(A, B);
    if (dcmp(A.r + B.r - d) <= 0)    return A.V() + B.V();//外离
    if (dcmp(A.r + d - B.r) <= 0 || (B.r + d - A.r) <= 0)    return max(A.V(), B.V());//内含
    
    db h1 = A.r - (sqr(A.r) + sqr(d) - sqr(B.r)) / 2 / d;//A的球冠高
    db h2 = B.r - (sqr(B.r) + sqr(d) - sqr(A.r)) / 2 / d;//B的球冠高
    return A.V() - A.Crown(h1) + B.V() - B.Crown(h2);
}

int main() {
    cin >> A.x >> A.y >> A.z >> A.r;
    cin >> B.x >> B.y >> B.z >> B.r;
    cout << fixed << setprecision(7) << solve() << '\n';
    return 0;
}
