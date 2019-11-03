typedef double Matrix[maxn][maxn+1];

void gauss_elimination(Matrix A, int n) {
	for (int i = 0; i < n; i++) {
		int r = i;
		for (int j = i + 1; j < n; j++)
			if (fabs(A[j][i]) > fabs(A[r][i]))
			    r = j;
		if (r != i)
			for (int j = 0; j <= n; j++)
				swap(A[i][j], A[r][j]);
		//开始消元
		// for (int j = i + 1; j < n; j++)
		// {
		// 	double f = A[j][i] / A[i][i];
		// 	for (int k = i; k <= n; k++)
		// 		A[j][k] -= f * A[i][k];
		// }
		for (int j = n; j >= i; j--)
			for (int k = i + 1; k < n; k++)
				A[k][j] -= A[k][i] / A[i][i] * A[i][j];
	}
	//A[i][n]为每个变量的解
	for (int i = n-1; ~i; i--) {
		for (int j = i + 1; j < n; j++)
			A[i][n] -= A[i][j] * A[j][n];
		A[i][n] /= A[i][i];
	}
}
