int F[1 << 20];

void Add(int x) {
	for (; x < maxn << 1; x += x&-x) F[x]++;
}

int Query(int k) {
	int ret = 0;
	per(i, 19, 0) {
		int bt = 1 << i;
		if (F[ret | bt] < k) {
			ret |= bt;
			k -= F[ret];
		}
	}
	return ret + 1;
}

Add(a);//把某个数加进去
Query(kth);//对于这个代码，问第k小的数

//比如顺序插入5，3，9，2后Query(4) = 9
