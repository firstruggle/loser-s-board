struct Seg {
	int l, r;
	int sum, maxx, minn;
};

struct tree {
	Seg t[maxn<<2];//线段树
	int addv[maxn<<2], setv[maxn<<2];//区间加、区间设置的懒标记

	void init(int c) {
		for (int i = 1; i <= (c<<2); i++) {
			addv[i] = 0;
			setv[i] = -1;
		}
	}

	void push_up(int p) {
		int ls = p << 1, rs = p << 1 | 1;
		t[p].sum = t[ls].sum + t[rs].sum;
		t[p].maxx = max(t[ls].maxx, t[rs].maxx);
		t[p].minn = min(t[ls].minn, t[rs].minn);
	}

	void build(int l, int r, int p) {
		t[p].l = l, t[p].r = r;
		if (l == r) {
			t[p].sum = t[p].maxx = t[p].minn = 0;
			return;
		}

		int mid = (l + r) >> 1;
		int ls = p << 1, rs = p << 1 | 1;
		build(l, mid, ls);
		build(mid+1, r, rs);
		push_up(p);
	}

	void push_down(int p) {
		int ls = p << 1, rs = p << 1 | 1;
		if (setv[p] >= 0) {
			t[ls].sum = setv[p]*(t[ls].r-t[ls].l+1);
			t[rs].sum = setv[p]*(t[rs].r-t[rs].l+1);
			t[ls].maxx = t[rs].maxx = setv[p];
			t[ls].minn = t[rs].minn = setv[p];
			setv[ls] = setv[rs] = setv[p];
			addv[ls] = addv[rs] = 0;
			setv[p] = -1;
		}
		if (addv[p]) {
			t[ls].maxx += addv[p];
			t[rs].maxx += addv[p];
			t[ls].minn += addv[p];
			t[rs].minn += addv[p];
			t[ls].sum += addv[p]*(t[ls].r-t[ls].l+1);
			t[rs].sum += addv[p]*(t[rs].r-t[rs].l+1);
			addv[ls] += addv[p];
			addv[rs] += addv[p];
			addv[p] = 0;
		}
	}

	void update(int l, int r, int k, int p, int flag) {
		if (l <= t[p].l && t[p].r <= r) {
			if (flag) {
				t[p].maxx = t[p].minn = k;
				t[p].sum = k*(t[p].r - t[p].l + 1);
				setv[p] = k;
				addv[p] = 0;
			} else {
				t[p].maxx += k;
				t[p].minn += k;
				t[p].sum += k*(t[p].r - t[p].l + 1);
				addv[p] += k;
			}
			return;
		}

		int mid = (t[p].l + t[p].r) >> 1;
		int ls = p << 1, rs = p << 1 | 1;
		push_down(p);
		if (l <= mid)	update(l, r, k, ls, flag);
		if (mid < r)	update(l, r, k, rs, flag);
		push_up(p);
	}

	Seg query(int l, int r, int p) {
		if (l <= t[p].l && t[p].r <= r)	return t[p];

		int mid = (t[p].l + t[p].r) >> 1;
		int ls = p << 1, rs = p << 1 | 1;
		push_down(p);
		if (l > mid)	return query(l, r, rs);
		if (r <= mid)	return query(l, r, ls);

		Seg a, b, ans;
		a = query(l, r, ls);
		b = query(l, r, rs);
		ans.sum = a.sum + b.sum;
		ans.maxx = max(a.maxx, b.maxx);
		ans.minn = min(a.minn, b.minn);
		return ans;
	}
}T[21];