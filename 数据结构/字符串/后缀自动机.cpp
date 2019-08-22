char s[maxn];

int last = 1, tot = 1;
struct Node {
	int ch[26];
	int len, fa, deep;
	void init() {
		memset(ch, 0, sizeof ch);
		deep = len = fa = 0;
	}
}sam[maxn << 1];

void Add(int c) {//每个节点比fa多出来的长度便是独有的子串
	int p = last, np = last = ++tot;
	sam[np].len = sam[p].len + 1;

  for (; p && !sam[p].ch[c]; p = sam[p].fa)
		sam[p].ch[c] = np;

	if (!p) sam[np].fa = 1;
	else {
		int q = sam[p].ch[c];
		if (sam[q].len == sam[p].len + 1) sam[np].fa = q;//作为q的儿子
		else {//与q一起作为新点的分化
			int nq = ++tot;
			sam[nq] = sam[q];
			sam[nq].len = sam[p].len + 1;
			sam[q].fa = sam[np].fa = nq;
			for (; p && sam[p].ch[c] == q; p = sam[p].fa)
				sam[p].ch[c] = nq;
		}
	}
}

int c[maxn], a[maxn << 1];
void RadixSort(int len) {//基数排序，使得节点有拓扑性
	memset(c, 0, sizeof c);
	for (int i = 1; i <= tot; i++)
		c[sam[i].len]++;
	for (int i = 1; i <= len; i++)
		c[i] += c[i - 1];
	for (int i = 1; i <= tot; i++)
		a[c[sam[i].len]--] = i;
}

int main() {
  scanf("%d %s", &n, s + 1);
  int len = strlen(s + 1);

  last = 1, tot = 1;
	for (int i = 1; i <= len * 2; i++)
		sam[i].init();
	for (int i = 1; s[i]; i++)
		Add(s[i] - 'a');
	RadixSort(len);
  for (int i = tot; i; i--) {
    int p = a[i];//从叶子后缀开始遍历
    ...
  }
}
