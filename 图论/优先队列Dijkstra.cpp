typedef pair<int,int> P;

vector <P> v[maxn];//pair里放pair<i, dis[i][j]>
for (int i = 0; i < n; i++)	d[i] = INF;
d[s] = 0;

priority_queue <P, vector<P>, greater<P> > Q;
Q.push(P(s, 0));

while (!Q.empty())
{
	int a = Q.top().first, b = Q.top().second;
	Q.pop();
	if (d[b] < a)	continue;
	for (auto i : v[b])
		if (d[i.first] > d[b] + i.second)
		{
			d[i.first] = d[b] + i.second;
			Q.push(P(d[i.first], i.first));
		}
}