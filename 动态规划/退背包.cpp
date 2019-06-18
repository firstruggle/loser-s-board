//首先对全部n个物品做一遍背包
//设f[V]为容量为V的背包的方案数
//如果当前第i个物品不存在，则遍历j，从f[j]中减去包含i的方案数
//g[j]为不含第i个且容量为j时的方案数
for (int i = 1; i <= n; i++) {
    if (可以含有第i个)  continue;
    for (int j = 0; j <= maxV; j++)
        if (j < v[i]) g[j] = f[j];
        else  g[j] = f[j] - g[j - v[i]];
}
