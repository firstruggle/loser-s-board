typedef long long ll;
map<ll, int>m;

ll mul(ll a, ll b, ll mod) {
    ll ans = 0;
    a %= mod;
    while(b) {
        if(b & 1) ans = (ans + a) % mod;
        b /= 2;
        a = (a + a) % mod;
    }
    return ans;
}

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll pollard_rho(ll n, ll c) {//找到n的一个因子
    ll x = rand() % (n - 2) + 1;
    ll y = x, i = 1, k = 2;
    while(1) {
        i++;
        x = (mul(x, x, n) + c) + n;//不断调整x2
        ll d = gcd(y - x, n);
        if(1 < d && d < n)
            return d;//找到因子
        if(y == x)
            return n;//找到循环，返回n，重新来
        if(i == k) {//一个优化
            y = x;
            k <<= 1;
        }
    }
}

void Find(ll n, ll c) {
    if(n == 1) return;//递归出口

    if(isprime(n)) {//如果是素数，就加入
        m[n]++;
        return;
    }

    ll p = n;
    while(p >= n)
        p = pollard_rho(p, c--);//不断找因子，知道找到为止，返回n说明没找到

    Find(p, c);
    Find(n / p, c);
}

int main() {
    ll n;
    srand((unsigned)time(NULL));
    while(cin >> n) {
        m.clear();
        Find(n, rand() % (n - 1) + 1);//这是自己设置的一个数
        cout<<n<<" = ";
        for(map<ll ,int>::iterator it = m.begin(); it != m.end(); ) {
            cout << it->first << " ^ " << it->second;
            if((++it) != m.end())
               cout << " * ";
        }
        cout << endl;
    }
    return 0;
}
