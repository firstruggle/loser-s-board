int len;
char s[maxn];
struct palindromic_tree {
	int len, fail;
	int ch[26];
}pt[maxn];
int tot, last;

void Add(int i, int c) {//每个点tot代表一种回文子串
	while (s[i - pt[last].len - 1] != s[i]) last = pt[last].fail;//寻找它能和谁构成回文串
	if (!pt[last].ch[c]) {//这个回文串还没出现过
		++tot;
		pt[tot].len = pt[last].len + 2;
		int j = pt[last].fail;
		while (s[i - pt[j].len - 1] != s[i]) j = pt[j].fail;//寻找当前回文串如果失配，最长的回文串应该在哪
		pt[tot].fail = pt[j].ch[c];
		pt[last].ch[c] = tot;//必须写最后
	}
	last = pt[last].ch[c];
	//cnt[last]++;如果需要记录出现多少次
}

void Init() {
	s[0] = '#';
	last = 0, tot = 1;
	rep(i, 0, len + 1) {
		pt[i].len = pt[i].fail = 0;
		memset(pt[i].ch, 0, sizeof pt[i].ch);
	}
	pt[0].fail = 1, pt[1].fail = 0;
	pt[0].len = 0, pt[1].len = -1;

	//rep(i, 0, len + 1) cnt[i] = 0;
}

int main() {
  scanf("%s", s + 1);
  len = strlen(s + 1);
  Init();
  for (int i = 1; i <= len; i++) Add(i, s[i] - 'a');
  for (int i = tot; i > 1; i--) {
    int f = pt[i].fail;
    cnt[f] += cnt[i];
  }
}
