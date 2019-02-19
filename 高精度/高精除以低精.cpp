void div(char *s, int n)
{
	int a[],c[];
	int lena = strlen(s);
	for (int i = 0; i < lena; ++i)
	{
		a[lena-i] = s[i] - '0';
	}

	int temp = 0;
	for (int i = 1; i <= lena; i++)
	{
		c[i] = (temp*10+a[i])/n;
		temp = (temp*10+a[i])%n;
	}

	int lenc = 1;
	while (!c[lenc] && lenc < lena)
		lenc++;

	for (int i = lenc; i <= lena; i++)
		cout << c[i];
}