ll l = 1, r = n;
while (l < r-2) {
    ll lmid = (l + r) >> 1;
    ll rmid = (lmid + r) >> 1;
    if (judge(lmid) < judge(rmid))
        l = lmid;
    else    r = rmid;
}
cout << max(judge(r), judge((l + r) >> 1)) << "\n";
