#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 107;
vector<int> path[maxn];
bool dp[maxn][maxn];
int s[maxn][3], pre[maxn][maxn], maps[maxn][maxn], num, one, two;
int color[maxn], n;

int abs(int x) {
    return x > 0 ? x : -x;
}
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
    if (tot - p == s[cnt][0]) {
        color[s[cnt][2]] = 1;
        dfs(s[cnt][2]);
    }
    else {
        color[s[cnt][2]] = 2;
        dfs(s[cnt][2]);
    }
    getAns(cnt - 1, pre[cnt][tot]);
}

int main() {
//    freopen("in.txt", "r", stdin);
    memset(dp, 0, sizeof(dp));
    memset(color, 0, sizeof(color));
    memset(maps, 0, sizeof(maps));
    memset(pre, 0, sizeof(pre));
    memset(s, 0, sizeof(s));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        while (1) {
            int a;
            scanf("%d", &a);
            if (!a) {
                break;
            }
            maps[i][a] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                if (maps[i][j] == 1 && maps[j][i] == 1) {
                    continue;
                }
                path[i].push_back(j);
//                printf("%d--->%d\n", i, j);
            }
        }
    }
    int flag = 0;
    num = 0;
    for (int i = 1; i <= n; i++) {
        if (!color[i]) {
            color[i] = 1;
            one = 1;
            two = 0;
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
        printf("No solution\n");
        return 0;
    }
    dp[0][0] = 1;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j <= n; j++) {
            if (dp[i][j]) {
                dp[i + 1][j + s[i + 1][0]] = 1;
                pre[i + 1][j + s[i + 1][0]] = j;
                dp[i + 1][j + s[i + 1][1]] = 1;
                pre[i + 1][j + s[i + 1][1]] = j;
            }
        }
    }
    for (int i = 1; i <= n - 1; i++) {
        if (dp[num][i]) {
            flag = 1;
            break;
        }
    }
    if (!flag) {
        printf("No solution\n");
        return 0;
    }
    int cnt_num = 0;
    int min_ans = n, loc = 0;
    for (int i = 1; i <= n - 1; i++) {
        if (dp[num][i]) {
            if (abs(n - i - i) < min_ans) {
                min_ans = abs(n - i - i);
                loc = i;
            }
        }
    }
    memset(color, 0, sizeof(color));
    getAns(num, loc);
    int ans_1 = 0, ans_2 = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 1) {
            ans_1++;
        }
        else {
            ans_2++;
        }
    }
    printf("%d", ans_1);
    for (int i = 1; i <= n; i++) {
        if (color[i] == 1) {
            printf(" %d", i);
        }
    }
    printf("\n%d", ans_2);
    for (int i = 1; i <= n; i++) {
        if (color[i] == 2) {
            printf(" %d", i);
        }
    }
    printf("\n");
    return 0;
}
