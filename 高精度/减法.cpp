void subtration(char *s, char *t)
{
	int a[],b[],c[];
	if (strlen(s) < strlen(t) || (strlen(s) == strlen(t) && strcmp(s,t) < 0))//t比s大则交换
	{
		char temp[];
		strcpy(temp,s);
		strcpy(s,t);
		strcpy(t,temp);
		cout << '-';//交换了减数和被减数结果为负数
	}

	int lena = strlen(s),lenb = strlen(t);
	for (int i = 0; i < lena; ++i)
	{
		a[lena-i] = s[i]-'0';
	}
	for (int i = 0; i < lenb; ++i)
	{
		b[lenb-i] = t[i]-'0';
	}

	int i;
	for (i = 1; i <= lena; i++)
	{
		if (a[i] < b[i])
		{
			a[i] += 10;
			a[i+1]--;
		}
		c[i] = a[i] - b[i];
	}

	while (c[i] == 0 && i > 1)
		i--;

	for (int j = i; j > 0; j--)
		cout << c[j];
}