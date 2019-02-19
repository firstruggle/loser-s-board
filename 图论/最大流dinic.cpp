//BZOJ1001 as an example
#include <bits/stdc++.h>
#define ri readint()
#define wi(x) writeint(x)
#define gc getchar()
#define pc(x) putchar(x)
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define init(a, b) memset(a, b, sizeof(a))
using namespace std;

const int inf = 1e9;
const int maxn = 1e6 + 5;
const int maxm = 6e6 + 1e4;

struct Edge {
	int to, cost, nxt;
}e[maxm];
int head[maxn], d[maxn], tot = 1;
int n, m, st, ed;
queue<int> Q;
/*
inline int readint() {
	int x = 0, s = 1, c = gc;
	while (c <= 32)	c = gc;
	if (c == '-')	s = -1, c = gc;
	for (; isdigit(c); c = gc)
		x = x * 10 + c - 48;
	return x * s;
}

inline void writeint(int x) {
	if (x > 9)	writeint(x/10);
	pc(x%10 + 48);
}

--------fast read & write------*/

inline void add(int x, int y, int z) {
	e[++tot].to = y, e[tot].cost = z, e[tot].nxt = head[x], head[x] = tot;
	e[++tot].to = x, e[tot].cost = z, e[tot].nxt = head[y], head[y] = tot;
}

bool bfs() {
	init(d, 0);
	while (Q.size())	Q.pop();

	Q.push(st), d[st] = 1;
	while (Q.size()) {
		int x = Q.front(); Q.pop();
		for (int i = head[x]; i; i = e[i].nxt) {
			if (e[i].cost && !d[e[i].to]) {
				Q.push(e[i].to);
				d[e[i].to] = d[x] + 1;
				if (e[i].to == ed)	return true;
			}
		}
	}

	return false;
}

int dinic(int x, int flow) {
	if (x == ed)	return flow;
	int rest = flow;
	for (int i = head[x]; i && rest; i = e[i].nxt) {
		if (e[i].cost && d[e[i].to] == d[x] + 1) {
			int k = dinic(e[i].to, min(rest, e[i].cost));
			if (!k)	d[e[i].to] = 0;
			e[i].cost -= k;
			e[i ^ 1].cost += k;
			rest -= k;
		}
	}

	return flow - rest;
}

int solve() {
	int maxflow = 0;
	st = 1, ed = n * m;
	while (bfs())	maxflow += dinic(st, inf);
	return maxflow;
}

int main() {
	/*
	n = ri, m = ri;
	rep(i, 1, n)
		rep(j, 1, m-1) {
			int c = ri;
			int x = (i-1)*m+j, y = x+1;
			add(x, y, c);
		}
	rep(i, 1, n-1)
		rep(j, 1, m) {
			int c = ri;
			int x = (i-1)*m+j, y = i*m+j;
			add(x, y, c);
		}
	rep(i, 1, n-1)
		rep(j, 1, m-1) {
			int c = ri;
			int x = (i-1)*m+j, y = i*m+j+1;
			add(x, y, c);
		}
	-------all read------*/
	wi(solve());
	return 0;
}