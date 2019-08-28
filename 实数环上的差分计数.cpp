#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef double db;
const int maxn = 1e5 + 5;
int n;
db l, v1, v2;
db a[maxn], ans[maxn];

db val(db x) {//make the value on the loop
    while (x < 0)   x += 2 * l;
    return x;
}

int main() {
    scanf("%d %lf %lf %lf", &n, &l, &v1, &v2);
    db len = v2 * l / (v1 + v2);
    //实数环上的差分，求2*l长度的环上被长度len包括的点的个数的概率
    vector<pair<db, int>> v;
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &a[i]);//点的位置
        v.emplace_back(val(a[i] - len), 1);//start, cnt should +1
        v.emplace_back(a[i], -1);//end, cnt should -1
    }
    
    v.emplace_back(2 * l, 0);//在0处断开环，形成一个终点
    sort(v.begin(), v.end());

    int cnt = 0;
    db cur = 0.0;//起点

    for (int i = 1; i <= n; i++) {
        if (a[i] < len) cnt++;//初始状态的数量
        else    break;
    }
    for (auto i : v) {
        ans[cnt] += i.first - cur;
        cur = i.first;
        cnt += i.second;
    }

    for (int i = 0; i <= n; i++)
        printf("%.20lf\n", ans[i] / 2 / l);
}
