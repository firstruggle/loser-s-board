#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

/*  本题答案是求带重边带自环的有向图上所有环长度的gcd  */

const int maxn = 1e5 + 5;
int n, m, ans;
int val[maxn];
vector<int> adj[maxn], len[maxn];
bool vis[maxn];

int gcd(int a, int b) {
	if (!a || !b)	return a + b;//ans初始为0所以有此写法
	return gcd(b, a % b);
}

void dfs(int cur, int id) {
	vis[cur] = 1;
	val[cur] = id;
	for (int i = 0; i < adj[cur].size(); i++) {
		int son = adj[cur][i], l = len[cur][i];
		if (!vis[son]) {
			dfs(son, id + l);
		} else if (val[son] != id + l) {//搜到过且不是上一个节点则为环
			ans = gcd(ans, abs(id + l - val[son]));
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		len[u].push_back(1);
		//本是有向图，但为了能计算回退长度所以加-1的虚边
		adj[v].push_back(u);
		len[v].push_back(-1);
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i])
			dfs(i, 0);
	if (!ans)	ans = n;
	return !printf("%d\n", ans);
}
