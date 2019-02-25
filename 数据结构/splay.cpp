//普通平衡树
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define R(x) scanf("%d", &x)
#define ri readint()
#define gc getchar()
#define wi(x) printf("%d\n", x)
#define ls(x) T[x].ch[0]
#define rs(x) T[x].ch[1]
using namespace std;

int readint() {
	int x = 0, s = 1, c = gc;
	while (c <= 32)	c = gc;
	if (c == '-')	s = -1, c = gc;
	for (; isdigit(c); c = gc)
		x = x * 10 + c - 48;
	return x * s;
}

struct node {
	int fa;
	int ch[2];
	int val, cnt;
	int size;
};
node T[100005];
int tot, root;

int lr(int x) {
	return x == rs(T[x].fa);
}

void Connect(int son, int fa, int way) {
	T[fa].ch[way] = son;
	T[son].fa = fa;
}

void push_up(int pos) {
	T[pos].size = T[ls(pos)].size + T[rs(pos)].size + T[pos].cnt;
}

void Rotate(int x) {
	int f = T[x].fa, gf = T[f].fa;
	int x_f = lr(x), f_gf = lr(f);
	Connect(T[x].ch[x_f^1], f, x_f);
	Connect(f, x, x_f^1);
	Connect(x, gf, f_gf);
	push_up(f);
	push_up(x);
}

void splay(int pos, int goal) {
	for (; T[pos].fa != goal; Rotate(pos)) {
		int f = T[pos].fa, gf = T[f].fa;
		if (gf != goal) {
			lr(f) ^ lr(pos) ? Rotate(pos) : Rotate(f);
		}
	}
	if (goal == 0)	root = pos;
}

void Insert(int x) {
	int pos = root, fa = 0;
	while (pos && T[pos].val != x) {
		fa = pos;
		pos = T[pos].ch[x > T[pos].val];
	}
	if (pos) {
		T[pos].cnt++;
	} else {
		pos = ++tot;
		if (fa)	T[fa].ch[x > T[fa].val] = pos;
		T[pos].ch[0] = T[pos].ch[1] = 0;
		T[pos].fa = fa;
		T[pos].val = x;
		T[pos].cnt = T[pos].size = 1;
	}
	splay(pos, 0);
}

int find(int x) {//数字val为x的位置
	int pos = root;
	if (!pos)	return 0;
	while (T[pos].ch[x > T[pos].val] && x != T[pos].val)
		pos = T[pos].ch[x > T[pos].val];
	splay(pos, 0);
	return pos;
}

int Next(int flag, int x) {//0为前驱，1为后继
	find(x);
	int pos = root;
	if (T[pos].val > x && flag)	return pos;
	if (T[pos].val < x && !flag)	return pos;
	pos = T[pos].ch[flag];
	while (T[pos].ch[flag^1]) {
		pos = T[pos].ch[flag^1];
	}
	return pos;
}

void Delet(int x) {//删除数字x
	int pos = find(x);
	if (!pos)	return;
	if (T[pos].cnt > 1) {
		T[pos].cnt--;
		T[pos].size--;
		return;
	} else {
		if (!ls(pos) && !rs(pos)) {
			root = 0;
			return;
		} else if (ls(pos) && rs(pos)) {
			int u = ls(pos);
			while (rs(u))	u = rs(u);
			splay(u, 0);
			Connect(rs(pos), u, 1);
			push_up(u);
		} else {
			if (ls(pos))	root = ls(pos);
			else	root = rs(pos);
			T[root].fa = 0;
		}
	}
}

int Rank(int x) {//数字x的排名
	find(x);
	return T[ls(root)].size + 1;
}

int Kth(int x) {//第x大的数
	int pos = root;
	if (T[pos].size < x)	return -1;
	while (true) {
		int lson = ls(pos);
		if (x > T[lson].size + T[pos].cnt) {
			x -= T[lson].size + T[pos].cnt;
			pos = rs(pos);
		} else {
			if (x > T[lson].size)	return T[pos].val;//这个题返回的是值
			pos = lson;
		}
	}
}

int main() {
	int n;
	for (n = ri; n; n--) {
		int op = ri, x = ri;
		if (op == 1)	Insert(x);
		else if (op == 2)	Delet(x);
		else if (op == 3)	wi(Rank(x));
		else if (op == 4)	wi(Kth(x));
		else	wi(T[Next(op - 5, x)].val);	
	}
	return 0;
}
