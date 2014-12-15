#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 2007;

vector<int> path[maxn];
vector<int> ans;


void dfs(int cnt) {
    while (path[cnt].size()) {
        int v = path[cnt].back();
        path[cnt].pop_back();
        dfs(v);
    }
    ans.push_back(cnt);
}

int main() {
//    freopen("in.txt", "r", stdin);
    int n, source;
    scanf("%d%d", &n, &source);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int d;
            scanf("%d", &d);
            if (i != j && d == 0)
                path[i].push_back(j);
        }
    }
    dfs(source);
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size() - 1; i++) {
        printf("%d %d\n", ans[i], ans[i + 1]);
    }
    return 0;
}
