//快读
template <typename T> void read(T &x) {
	x = 0;
	int s = 1, c = getchar();
	for (; !isdigit(c); c = getchar())
		if (c == '-')	s = -1;
	for (; isdigit(c); c = getchar())
		x = x * 10 + c - 48;
	x *= s;
}

template <typename T> void write(T x) {
	if (x < 0)	x = -x, putchar('-');
	if (x > 9)	write(x / 10);
	putchar(x % 10 + '0');
}

template <typename T> void writeln(T x) {
	write(x);
	puts("");
}

//fread
int pos,len;
char buf[1005];

int xchar() {
	if (pos == len)
		pos = 0, len = fread(buf, 1, 1005, stdin);
	return buf[pos++];
}

int readint() {
	int x = 0, s = 1, c = xchar();
	while (c <= 32)	
		c = xchar();
	if (c == '-')
		s = -1, c = xchar();
	for (; isdigit(c); c = xchar())
		x = x * 10 + c - '0';
	return x * s;
}


--------------------网上看到的另一种--------------------------
struct ios
{
	inline char read()
	{
		static const int LEN = 1<<18|1;
		static char buf[LEN], *s, *t;
		return (s==t)&&(t = (s=buf)+fread(buf, 1, LEN, stdin)), s==t?-1:*s++;
	}
	template<typename T> inline ios &operator >> (T &x)
	{
		static char c, boo;
		for (c = read(), boo = 0; !isdigit(c); c = read())
		{
			if (c == -1)	return *this;
			boo |= c=='-';
		}
		for ( x = 0; isdigit(c); c = read())
			x = x*10 + c^'0';
		return *this;
	}
}in;

int a;
in >> a;

------------------王逸松的快读快写-----------------------
namespace IO {
    const int BUF_SIZE = 1 << 15;
    char in_buf[BUF_SIZE], out_buf[BUF_SIZE];
    char *p_in_buf = in_buf + BUF_SIZE;
    char *p_out_buf = out_buf;
    
    
    inline char get_char() {
        if (p_in_buf == in_buf + BUF_SIZE) {
            fread(in_buf, 1, BUF_SIZE, stdin), p_in_buf = in_buf;
        }
        return *(p_in_buf++);
    }
    
    inline void put_char(char x) {
        if (p_out_buf == out_buf + BUF_SIZE) {
            fwrite(out_buf, 1, BUF_SIZE, stdout), p_out_buf = out_buf;
        }
        *(p_out_buf++) = x;
    }
    
    inline void flush() {
        if (p_out_buf != out_buf) {
            fwrite(out_buf, 1, p_out_buf - out_buf, stdout);
            p_out_buf = out_buf;
        }
    }
}

#define getchar() IO::get_char()
#define putchar(x) IO::put_char(x)

inline int getint() {
    int x = 0;
    char c = getchar();
    while (c <= 32) c = getchar();
    while (c > 32) x = x * 10 + c - 48, c = getchar();
    return x;
}

inline int getint(char &c) {
    int x = 0;
    c = getchar();
    while (c <= 32) c = getchar();
    while (c > 32) x = x * 10 + c - 48, c = getchar();
    return x;
}

template <class T>
inline void _putint(T x) {
    return x ? _putint(x / 10), putchar(48 + x % 10), void() : void();
}

template <class T>
inline void putint(T x) {
    return x == 0 ? putchar('0'), void() : _putint(x), void();
}

inline void getline(char *s) {
    char c = getchar();
    while (c == '\n') c = getchar();
    while (c != '\n') *(s++) = c, c = getchar();
    *s = 0;
}
