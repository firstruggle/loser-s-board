rep(i, 1, 9) {//九位数
    rep(j, 0, 9) c[j].clear(), d[j].clear();
    //从个位开始排的，first代表还没排的，second是已经排完的数，first末端接上second就是原数
    rep(j, 0, (1 << n) - 1) c[s[j].first % 10].push_back(pll(s[j].first / 10, s[j].second));
    rep(j, 0, (1 << m) - 1) d[t[j].first % 10].push_back(pll(t[j].first / 10, t[j].second));
    rep(j, 0, 9) {//题目需要。j枚举这一位是几，k1代表与其相加为4且不依靠进位则应该是几，k2依靠进位
        k1 = (14 - j) % 10, k2 = (13 - j) % 10;
        ans += Solve(j);
    }
    //经过下边这轮，s和t已经是按后i位排完序的了
    int p = 0;
    rep(j, 0, 9) for (pll k : c[j]) {
        s[p++] = pll(k.first, k.second + base * j);
    }
    p = 0;
    rep(j, 0, 9) for (pll k : d[j]) {
        t[p++] = pll(k.first, k.second + base * j);
    }
    base *= 10;
}
