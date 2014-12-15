#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 103;
int n, color[maxn];
vector<int> path[maxn];

bool dfs(int cnt, int cnt_color) {
    if (color[cnt] != -1) {
        if (color[cnt] == cnt_color) {
            return true;
        }
        return false;
    }
    color[cnt] = cnt_color;
    for (int i = 0; i < path[cnt].size(); i++) {
        int next = path[cnt][i];
        if (!dfs(next, !cnt_color)) {
            return false;
        }
    }
    return true;
}
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        while (1) {
            int a;
            scanf("%d", &a);
            if (!a) {
                break;
            }
            path[a].push_back(i);
            path[i].push_back(a);
        }
    }
    memset(color, -1, sizeof(color));
    int flag = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            if (!dfs(i, 0)) {
                flag = 1;
                break;
            }
        }
    }
    if (flag) {
        printf("-1\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d", color[i]);
    }
    printf("\n");
    return 0;
}
