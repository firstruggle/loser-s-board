void get_Next(char *p, int *Next)
{
	int m = strlen(p);
	Next[0] = Next[1] = 0;
	for (int i = 1; i < m; i++)
	{
		int j = Next[i];
		while (j && p[i] != p[j])
			j = Next[j];
		Next[i+1] = p[i]==p[j]?j+1:0;
	}
}//PS：length-Next[length]是循环节的长度

void find(char *t, char *p, int Next)//t是主串，p是子串
{
	int n = strlen(t), m = strlen(p), j=0;
	get_Next(p, Next);

	for (int i = 0; i < n; i++)
	{
		while (j && p[j] != t[i])
			j = Next[j];
		if (p[j] == t[i])
			j++;
		if (j == m)
			printf("%d\n", i-m+1);
	}
}