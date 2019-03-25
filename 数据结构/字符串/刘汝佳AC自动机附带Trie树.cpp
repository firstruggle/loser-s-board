struct AC_Automata {
	int ch[maxnod][26];//Trie树转移
	int cnt[155];//每个子串出现了几次
	int val[maxnod];//某节点是否为子串结尾以及是哪个串的结尾
	int f[maxnod];//失配，转移到别的树枝继续找
	int last[maxnod];//找到了后缀相同的其他可行子串
	int sz;

	void init() {
		sz = 1;
		mp.clear();//与ac自动机无关
		memset(ch[0], 0, sizeof ch[0]);
		memset(cnt, 0, sizeof cnt);
	}

	int idx(char c) { return c - 'a'; }

	void insert(char* s, int v) {//Trie树的插入
		int u = 0, n =strlen(s);
		for (int i = 0; i < n; ++i) {
			int c = idx(s[i]);
			if (!ch[u][c]) {
				memset(ch[sz], 0, sizeof ch[sz]);
				val[sz] = 0;
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
		val[u] = v;
	}

	void getfail() {
		queue<int> Q;
		f[0] = 0;
		for (int i = 0; i < 26; i++) {
			int u = ch[0][i];
			if (u) {
				f[u] = last[u] = 0;
				Q.push(u);
			}
		}
		while (!Q.empty()) {
			int r = Q.front(); Q.pop();
			for (int c = 0; c < 26; c++) {
				int u = ch[r][c];
				if (!u)	continue;
				Q.push(u);
				int v = f[r];
				while (v && !ch[v][c])	v = f[v];//当前这个不行看看别人行不行
				f[u] = ch[v][c];
				last[u] = val[f[u]] ? f[u] : last[f[u]];
			}
		}
	}

	void Success(int j) {
		if (j) {
			cnt[val[j]]++;
			Success(last[j]);
		}
	}

	void find(char* T) {
		int n = strlen(T);
		for (int i = 0, j = 0; i < n; ++i) {
			int c = idx(T[i]);
			while (j && !ch[j][c])	j = f[j];
			j = ch[j][c];
			if (val[j])	Success(j);
			else if (last[j])	Success(last[j]);
		}
	}
}ac;
