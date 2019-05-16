/*目前在用的*/
//val是根据题意改的，板子其它部分也是随使用而改变或添加
struct Aho_Corasick_Automaton {
    int ch[N][26];//Trie树的转移
    int val[N];//根据题意赋值。有值则意味着某子串末尾
    int fail[N];//失配，转移到别的树枝接着找
    int sz;//注意这个板子sz一定是要从1开计
    
    void init() {
        sz = 0;
        memset(ch[0], 0, sizeof ch[0]);
    }

    void insert(char *s, int id) {//Trie的插入
        int len = strlen(s), now = 0;

        for (int i = 0; i < len; i++){
            int c = s[i] - 'a';
            if (!ch[now][c]) {
                sz++;
                memset(ch[sz], 0, sizeof ch[sz]);
                val[sz] = 0;
                ch[now][c] = sz;
            }
            now = ch[now][c];
        }
        val[now] = id;
    }

    void getfail(){
        queue<int> Q;
        for (int i = 0; i < 26; i++)
            if (ch[0][i])
                fail[ch[0][i]] = 0, Q.push(ch[0][i]);//第二层指向根
        while (!Q.empty()){
            int u = Q.front(); Q.pop();
            for (int i = 0; i < 26; i++)
                if (ch[u][i])
                    fail[ch[u][i]] = ch[fail[u]][i], Q.push(ch[u][i]);//指向其他枝上同样的字母
                else ch[u][i] = ch[fail[u]][i];//使得find时半路突然失配时还能一下拐回去
        }
    }

    void find(char *T){
        int len = strlen(T), now = 0;

        for (int i = 0; i < len; i++){
            now = ch[now][T[i] - 'a'];
            for (int t = now; t; t = fail[t])//事实上这是一个不断缩短后缀的过程
                if (val[t]) Ans[val[t]].cnt++;
        }
    }
}ac;




//刘汝佳的，太慢会卡掉
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
