//给定年月日迅速计算是星期几
int calc(int y, int m, int d) {
    if (m == 1 || m == 2) m += 12, y--;
    return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;
}
