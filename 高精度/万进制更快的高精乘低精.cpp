//此处以一万进制为例
void mul(int x[], int n)//高精与低精传入
{
	int a = 0,len = 1;

	for (int i = 1; i <= len; i++)
	{
		x[i] = x[i]*n + a;
		a = x[i]/10000;
		x[i] %= 10000;
		if (a > 0 && i >= len)
			len++;
	}
	cout << x[len];
	for (int i = len-1; i > 0; i--)
		printf("%04d", x[i]);
}