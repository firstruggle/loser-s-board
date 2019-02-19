//辗转相除法
int gcd(int a, int b)
{
	return b ? gcd(b, a%b) : a;
}

//更相减损术
#define ll long long
ll stein(ll a, ll b)
{
	if (!a)	return b;
	if (!b)	return a;

	if (a%2 == 0 && b%2 == 0)	return 2*stein(a>>1, b>>1);
	else if (a%2 == 0)	return stein(a>>1, b);
	else if (b%2 == 0)	return stein(a, b>>1);
	
	return stein(abs(a-b), min(a, b));
}