//常规矩阵幂
struct Matrix {
	ll v[2][2];

	Matrix() {
		init(v, 0);
	}

	friend Matrix operator * (Matrix A, Matrix B) {
		Matrix ret;
		rep(i, 0, 1)
			rep(j, 0, 1)
				rep(k, 0, 1)
					ret.v[i][j] = (ret.v[i][j] + (A.v[i][k] * B.v[k][j]) % mod) % mod;
		return ret;
	}

	friend Matrix operator ^ (Matrix A, int k) {
		Matrix ret;
		ret.v[0][0] = ret.v[1][1] = 1;
		for (; k; k >>= 1) {
			if (k & 1)	ret = ret * A;
			A = A * A;
		}
		return ret;
	}
};


//循环矩阵相乘还是循环矩阵
//可以通过其中一行推出其他行，故只需记录第一行，复杂度O(n^2)
struct Matrix {
	db v[maxn];
	Matrix() {
		memset(v, 0, sizeof v);
	}

	friend Matrix operator * (Matrix A, Matrix B) {
		Matrix ret;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				ret.v[i] += A.v[j] * B.v[(i - j + n) % n];
			}
		}
		return ret;
	}

	friend Matrix operator ^ (Matrix A, int k) {
		Matrix res;
		res.v[0] = 1.0;
		for (; k; k >>= 1) {
			if (k & 1)	res = res * A;
			A = A * A;
		}
		return res;
	}
};
