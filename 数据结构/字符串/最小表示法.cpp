/*
 *最小表示法是求与某个字符串循环同构的所有字符串中，字典序最小的串是哪个。
 *比如说一个字符串jdrakioi，它长为8，也就是说最多有八种循环同构的方法。
 *jdrakioi、drakioij、rakioijd、akioijdr、kioijdra、ioijdrak、oijdraki、ijdrakio。
 */
int getmin(char *s) {
    int i = 0, j = 1, k = 0;
    //从0开始，i为某位置，j为某位置，k为长度
    while (i < n && j < n && k < n) {
        int t = s[(i + k) % n] - s[(j + k) % n];
        if (!t) k++;//相同
        else {
            if (t > 0)  i += k + 1;
            else  j += k + 1;
            if (i == j) j++;
            k = 0;
        }
    }
    return i < j ? i : j;
}
