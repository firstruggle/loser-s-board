void dfs(int cur) {//first是下一个点，second是当前边
    while (!adj[cur].empty()) {
        auto tmp = adj[cur].back();
        adj[cur].pop_back();
        if (!vis[tmp.second]) {
            vis[tmp.second] = 1;
            dfs(tmp.first);
            ans[cnt++] = tmp.first;
        }
    }
}

int main() {
    //...建图
    vector<int> v;
    for (int i = 1; i <= tot; i++) {
        if (adj[i].size() % 2 == 1)
            v.push_back(i);
    }
    if (v.size() == 2) {
        dfs(v[0]);
        ans[cnt++] = v[0];
    } else if(v.size() == 0) {
        dfs(1);
        ans[cnt++] = 1;
    }
}
