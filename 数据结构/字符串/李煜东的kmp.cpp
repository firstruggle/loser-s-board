void Get_Next(char* s, int len) {
    Next[1] = 0;
    for (int i = 2, j = 0; i <= len; i++) {
        while (j > 0 && s[i] != s[j + 1]) j = Next[j];
        if (a[i] == a[j + 1]) j++;
        Next[i] = j;
    }
}

void Get_f(char* s, char* T, int LEN) {
    for (int i = 1, j = 0; i <= LEN; i++) {
        while (j > 0 && (j == n || T[i] != s[j + 1])) j = Next[j];
        if (T[i] == s[j + 1]) j++;
        f[i] = j;
        if (f[i] == n)  //balabala……
    }
}
