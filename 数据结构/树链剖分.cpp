#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include <climits>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <fstream>
#define ri readint()
#define gc getchar()
#define R(x) scanf("%d", &x)
#define W(x) printf("%d\n", x)
#define init(a, b) memset(a, b, sizeof(a))
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define irep(i, a, b) for (int i = a; i >= b; i--)
#define ls  p << 1
#define rs	p << 1 | 1
using namespace std;

typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> P;
const int inf = 0x3f3f3f3f;
const ll INF = 1e18;

inline int readint() {
	int x = 0, s = 1, c = gc;
	while (c <= 32)	c = gc;
	if (c == '-')	s = -1, c = gc;
	for (; isdigit(c); c = gc)
		x = x * 10 + c - 48;
	return x * s;
}

const int maxn = 1e5 + 5;
int n, m, root, mod, a[maxn];

/**树剖所需**/
int deep[maxn], fa[maxn], size[maxn], son[maxn], top[maxn], id[maxn], rnk[maxn], cnt;

/**建树所需**/
struct Edge {
	int to, nxt;
}e[maxn << 1];
int tot, head[maxn];

/**线段树所需**/
struct Seg {
	int l, r, sum, laz;
}t[maxn << 2];

inline void add(int u, int v) {
	e[++tot].to = v, e[tot].nxt = head[u], head[u] = tot; 
}

/****线段树部分****/

inline int len(int p) {//宏定义出大锅了，调了半天，改成函数就A了
	return t[p].r - t[p].l + 1;
}

inline void push_up(int p) {
	t[p].sum = (t[ls].sum + t[rs].sum) % mod;
}

inline void push_down(int p) {
	if (t[p].laz) {
		t[ls].laz += t[p].laz;
		t[rs].laz += t[p].laz;
		t[ls].sum = (t[ls].sum + len(ls) * t[p].laz % mod) % mod;
		t[rs].sum = (t[rs].sum + len(rs) * t[p].laz % mod) % mod;
		t[p].laz = 0;
	}
}

void build(int l, int r, int p) {
	t[p].l = l, t[p].r = r;
	if (l == r) {
		t[p].laz = 0;
		t[p].sum = rnk[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, ls);
	build(mid + 1, r, rs);
	push_up(p);
}

void segupd(int l, int r, int p, int k) {
	if (l <= t[p].l && t[p].r <= r) {
		t[p].sum = (t[p].sum + len(p) * k % mod) % mod;
		t[p].laz += k;
		return;
	}
	int mid = (t[p].l + t[p].r) >> 1;
	push_down(p);
	if (l <= mid)	segupd(l, r, ls, k);
	if (mid < r)	segupd(l, r, rs, k);
	push_up(p);
}

int segask(int l, int r, int p) {
	if (l <= t[p].l && t[p].r <= r)	return t[p].sum;
	int mid = (t[p].l + t[p].r) >> 1;
	int res = 0;
	push_down(p);
	if (l <= mid)	res = (res + segask(l, r, ls)) % mod;
	if (mid < r)	res = (res + segask(l, r, rs)) % mod;
	return res;
}

/****树剖部分****/

void dfs1(int u, int f, int depth) {
	deep[u] = depth;
	fa[u] = f;
	size[u] = 1;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == f)	continue;
		dfs1(v, u, depth + 1);
		if (size[v] > size[son[u]])	son[u] = v;
		size[u] += size[v];
	}
}

void dfs2(int u, int topf) {
	id[u] = ++cnt;
	rnk[cnt] = a[u];
	top[u] = topf;
	if (!son[u])	return;
	dfs2(son[u], topf);
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v != son[u] && v != fa[u])
			dfs2(v, v);
	}
}

void Update(int x, int y, int z) {
	while (top[x] != top[y]) {
		if (deep[top[x]] < deep[top[y]])	swap(x, y);
		segupd(id[top[x]], id[x], 1, z);
		x = fa[top[x]];
	}
	if (deep[x] > deep[y])	swap(x, y);
	segupd(id[x], id[y], 1, z);
}

int Query(int x, int y) {
	int ans = 0;
	while (top[x] != top[y]) {
		if (deep[top[x]] < deep[top[y]])	swap(x, y);
		ans = (ans + segask(id[top[x]], id[x], 1)) % mod;
		x = fa[top[x]];
	}
	if (deep[x] > deep[y])	swap(x, y);
	ans = (ans + segask(id[x], id[y], 1)) % mod;
	return ans;
}

int main() {
	n = ri, m = ri, root = ri, mod = ri;
	rep(i, 1, n) {
		a[i] = ri;
		a[i] %= mod;
	}
	rep(i, 1, n - 1) {
		int x = ri, y = ri;
		add(x, y);
		add(y, x);
	}
	dfs1(root, 0, 1);
	dfs2(root, root);
	build(1, n, 1);
	
	while (m--) {
		int op = ri, x, y, z;
		if (op == 1) {
			x = ri, y = ri, z = ri;
			Update(x, y, z % mod);
		} else if (op == 2) {
			x = ri, y = ri;
			W(Query(x, y));
		} else if (op == 3) {
			x = ri, z = ri;
			segupd(id[x], id[x] + size[x] - 1, 1, z % mod);
		} else {
			x = ri;
			W(segask(id[x], id[x] + size[x] - 1, 1));
		}
	}
	return 0;
}
