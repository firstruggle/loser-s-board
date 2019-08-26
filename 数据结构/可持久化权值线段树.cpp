//区间第k小的数
int Sz, root[maxn];
struct Seg {
    int sum, l, r;//sum是某值出现次数
}t[maxn * 20];//n*log，注意是n不是值域

int Build(int l, int r) {
    int p = ++Sz;
    if (l == r) {
        t[p].sum = t[p].l = t[p].r = 0;
        return Sz;
    }
    int mid = (l + r) >> 1;
    t[p].l = Build(l, mid);
    t[p].r = Build(mid + 1, r);
    t[p].sum = t[ls(p)].sum + t[rs(p)].sum;
    return p;
}

int Update(int l, int r, int last, int k) {
    int p = ++Sz;
    t[p].l = t[last].l, t[p].r = t[last].r, t[p].sum = 0;
    if (l == r) {
        t[p].sum = t[last].sum + 1;
        return p;
    }
    int mid = (l + r) >> 1;
    if (k <= mid)   t[p].l = Update(l, mid, ls(last), k);
    else    t[p].r = Update(mid + 1, r, rs(last), k);
    t[p].sum = t[ls(p)].sum + t[rs(p)].sum;
    return p;
}

int Query(int l, int r, int last, int p, int k) {
    if (l == r) return l;
    int res = t[ls(p)].sum - t[ls(last)].sum;
    int mid = (l + r) >> 1;
    if (res >= k)    return Query(l, mid, ls(last), ls(p), k);
    else    return Query(mid + 1, r, rs(last), rs(p), k - res);
}

int main() {
    //通常离散化一波
    root[0] = Build(1, 值域最大值);
    rep(i, 1, n) root[i] = Update(1, 值域最大值, root[i - 1], a[i]);
    rep(i, 1, Q) {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);
        res = Query(1, 值域最大值, root[l - 1], root[r], k);
    }
    return 0;
}
