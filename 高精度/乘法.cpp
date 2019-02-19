void multi(char *s, char *t)//高精乘高精
{
	int a[],b[],c[];
	int lena = strlen(s),lenb = strlen(t);
	for (int i = 0; i < lena; ++i)
	{
		a[lena-i] = s[i] - '0';
	}
	for (int i = 0; i < lenb; ++i)
	{
		b[lenb-i] = t[i] - '0';
	}

	for (int i = 1; i <= lena; i++)
	{
		int temp = 0;
		for (int j = 1; j <= lenb; j++)
		{
			c[i+j-1] += a[i]*b[j]+temp;
			temp = c[i+j-1]/10;
			c[i+j-1] %= 10;
		}
		c[i+lenb] = temp;
	}

	int lenc = lena + lenb;
	while (c[lenc] == 0 && lenc > 1)
		lenc--;
	for (int i = lenc; i > 0; i--)
		cout << c[i];
}

void multi(char *s, int n)//高精乘低精
{
	int a[];
	int lena = strlen(s);
	for (int i = 0; i < lena; ++i)
	{
		a[i] = s[i] - '0';
	}

	int temp = 0;
	for (int i = 1; i <= lena; i++)
	{
		a[i] = a[i]*n + temp;
		temp = a[i]/10;
		a[i] %= 10;
		if (temp && i == lena)
			lena]++;
	}

	for (int i = lena; i > 0; i--)
		cout << a[i];
}