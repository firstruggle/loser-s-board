//普通平衡树
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define R(x) scanf("%d", &x)
#define ri readint()
#define gc getchar()
#define wi(x) printf("%d\n", x)
#define ls T[x].ch[0]
#define rs T[x].ch[1]
#define root T[0].ch[1]
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
int tot;

int lr(int x, int fa) {
	return x == T[fa].ch[1];
}

void Connect(int x, int fa, int way) {
	T[fa].ch[way] = x;
	T[x].fa = fa;
}

void push_up(int x) {
	T[x].size = T[ls].size + T[rs].size + T[x].cnt;
}

void Rotate(int x) {
	int f = T[x].fa, gf = T[f].fa;
	int x_f = lr(x, f), f_gf = lr(f, gf);
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
			(T[gf].ch[0] == f) ^ (T[f].ch[0] == pos) ? Rotate(pos) : Rotate(f);
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
		if (!T[pos].ch[0] && !T[pos].ch[1]) {
			root = 0;
			return;
		} else if (T[pos].ch[0] && T[pos].ch[1]) {
			int u = T[pos].ch[0];
			while (T[u].ch[1])	u = T[u].ch[1];
			splay(u, 0);
			Connect(T[pos].ch[1], u, 1);
			push_up(u);
		} else {
			if (T[pos].ch[0])	root = T[pos].ch[0];
			else	root = T[pos].ch[1];
			T[root].fa = 0;
		}
	}
}

int Rank(int x) {//数字x的排名
	find(x);
	return T[T[root].ch[0]].size + 1;
}

int Kth(int x) {//第x大的数
	int pos = root;
	if (T[pos].size < x)	return -1;
	while (true) {
		int lson = T[pos].ch[0];
		if (x > T[lson].size + T[pos].cnt) {
			x -= T[lson].size + T[pos].cnt;
			pos = T[pos].ch[1];
		} else {
			if (x > T[lson].size)	return T[pos].val;
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
