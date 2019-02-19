void add(char *s, char *t)
{
	int a[],b[],c[];
	int lena = strlen(s);
	int lenb = strlen(t);
	for (int i = 0; i < lena; ++i)
	{
		a[lena-i] = s[i]-'0';
	}
	for (int i = 0; i < lenb; ++i)
	{
		b[lenb-i] = t[i]-'0';
	}

	int i;
	int temp = 0;
	for (i = 1; i <= max(lena,lenb); i++)
	{
		c[i] = a[i]+b[i]+temp;
		temp = c[i]/10;
		c[i]%=10;
	}

	if (temp)	c[i] = temp;
	else	i--;

	for (int j = i; j > 0; j--)
		cout << c[i];
}