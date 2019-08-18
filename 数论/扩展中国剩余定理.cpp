//n个关系，为ans = bb[i](% aa[i]) ，求最小非负ans
//注意当组数变多时可能得使用Java大整数
    int flag = 1;
    ll aa[maxn], bb[maxn];
    ll x, y, ans, M, a, b, c, r, bg;

    for (int i = 1; i <= n; i++) {
       read(aa[i]), read(bb[i]);
    }
    M = aa[1]; ans = bb[1];
    for (int i = 2; i <= n; i++) {
        x = y = 0;
        a = M; b = aa[i];
        c = ((bb[i] - ans) % b + b) % b;
        r = exgcd(a, b, x, y);
        bg = b / r;
        if (c % r != 0) {
            flag = -1; break;//无解
        }
        x = c / r % bg * x % bg;
        ans += x * M;
        M *= bg;
        ans = (ans % M + M) % M;
    }
    if (flag > 0) print(ans);
