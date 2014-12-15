#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int maxn = 500;


int color[maxn], n, m, num, one, two;
int s[maxn][3];
int dp[maxn][maxn];
int pre[maxn][maxn];
vector<int> path[maxn];

int dfs(int cnt) {
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        if (color[v] == color[cnt]) {
            return false;
        }
        if (color[v]) {
            continue;
        }
        color[v] = 3 - color[cnt];
        if (color[v] == 1) {
            one++;
        }
        else {
            two++;
        }
        if (!dfs(v)) {
            return false;
        }
    }
    return true;
}

void getAns(int cnt, int tot) {
    if (cnt == 0) {
        return ;
    }
    int p = pre[cnt][tot];
    if (tot - p == s[cnt][1]) {
        color[s[cnt][2]] = 2;
        dfs(s[cnt][2]);
    }
    else {
        color[s[cnt][2]] = 1;
        dfs(s[cnt][2]);
    }
    getAns(cnt - 1, p);
}
int main() {
//    freopen("in.txt", "r", stdin);
    memset(color, 0, sizeof(color));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        path[a].push_back(b);
        path[b].push_back(a);
    }
    int flag = 0;
    num = 0;
    for (int i = 1; i <= n * 2; i++) {
        if (!color[i]) {
            one = 1;
            two = 0;
            color[i] = 1;
            if (!dfs(i)) {
                flag = 1;
                break;
            }
            num++;
            s[num][0] = one;
            s[num][1] = two;
            s[num][2] = i;
        }

    }
    if (flag) {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j <= 2 * n; j++) {
            if (dp[i][j]) {
                dp[i + 1][j + s[i + 1][0]] = 1;
                pre[i + 1][j + s[i + 1][0]] = j;
                dp[i + 1][j + s[i + 1][1]] = 1;
                pre[i + 1][j + s[i + 1][1]] = j;
            }
        }
    }
    if (!dp[num][n]) {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    memset(color, 0, sizeof(color));
    getAns(num, n);
    for (int i = 1; i <= 2 * n; i++) {
        if (color[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
    for (int i = 1; i <= 2 * n; i++) {
        if (color[i] == 2) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}
