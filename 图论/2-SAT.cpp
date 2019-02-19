struct TWOSAT
{
	int n;
	vector<int> G[maxn*2];
	bool mark[maxn*2];
	int record[maxn*2], t;

	void init(int n)
	{
		this->n = n;
		for (int i = 0; i < n*2; i++)	G[i].clear();
		memset(mark, false, sizeof(mark));
	}

	bool dfs(int u)
	{
		if (mark[u^1])	return false;
		if (mark[u])	return true;

		mark[u] = true;
		record[t++] = u;
		for (int i : G[u])
			if (!dfs(i))
				return false;
		return true;
	}

	void add(int x, int xval, int y, int yval)
	{
		x = x*2 + xval;
		y = y*2 + yval;
		G[x^1].push_back(y);
		G[y^1].push_back(x);
	}

	bool solve()
	{
		for (int i = 0; i < n*2; i += 2)
			if (!mark[i] && !mark[i+1])
			{
				t = 0;
				if (!dfs(i))
				{
					while (t)	mark[record[--t]] = false;
					if (!dfs(i+1))	return false;
				}
			}
		return true;
	}
};