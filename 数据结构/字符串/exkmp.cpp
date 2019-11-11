int Next[maxn], ext[maxn], n, m;
char s[maxn], t[maxn];

//貌似不用初始化
//Next[i]是t串的第i位匹配t串自己的lcp
//ext[i]是t串的第i位匹配s串的lcp
//所以只写上半部分求Next的部分就已经有z_algorithm的功能了
void exkmp(char *s, int n, char *t, int m) {
    int p = 0, id = 0;
    Next[1] = m;
    for (int i = 2; i <= m; i++) {
        int j = Next[i - id + 1];
        if (i + j > p)
            for (j = max(p - i, 0); i + j <= m && t[j + 1] == t[i + j]; j++);
        Next[i] = j;
        if (i + j - 1 > p)
            id = i, p = i + j - 1;
    }
    id = p = 0;
    for (int i = 1; i <= n; i++) {
        int j = Next[i - id + 1];
        if (i + j > p)
            for (j = max(p - i, 0); i + j <= n && t[j + 1] == s[i + j]; j++);
        ext[i] = j;
        if (i + j - 1 > p)
            id = i, p = i + j - 1;
    }
}
