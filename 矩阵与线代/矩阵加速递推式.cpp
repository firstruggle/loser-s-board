//常规矩阵幂
struct Matrix {
    int v[maxn][maxn], n;
    
    Matrix(int n) { memset(v, 0, sizeof v); this->n = n; }
    
    Matrix operator * (const Matrix &A) const {
        Matrix ret(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    ret.v[i][j] = ((ll)ret.v[i][j] + (ll)v[i][k] * A.v[k][j] % mod) % mod;
        return ret;
    }
    
    Matrix operator ^ (int b) const {
        Matrix ret(n);
        Matrix A = *this;
        for (int i = 0; i < n; i++)
            ret.v[i][i] = 1;
        for (; b; b >>= 1) {
            if (b & 1)    ret = ret * A;
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
