#include <cstdio>
#include <string.h>
#include <vector>

using namespace std;
const int MAX_NUMBER = 50;
vector<int> path[MAX_NUMBER];
vector<int> ans[MAX_NUMBER];
int vis[MAX_NUMBER];
int cnt;
int n, edge_number, flag;

void dfs(int people, int number, int cnt) {
    ans[cnt].push_back(people);
    for (int i = 0; i < path[people].size(); i++) {
        int next_people = path[people][i];
        if (!vis[path[people][i]]) {
            vis[next_people] = 1;
            number++;
            dfs(next_people, number, cnt);
        }
    }
}

int main() {

    int cnt = 0;
    flag = 0;
    memset(vis, 0, sizeof(vis));
    scanf("%d%d", &n, &edge_number);
    for (int i = 1; i <= edge_number; i++) {
        int start, end;
        scanf("%d%d", &start, &end);
        path[start].push_back(end);
        path[end].push_back(start);
    }
    for (int i = 1; i <= n && !flag; i++) {
        if (!vis[i]) {
            cnt++;
            vis[i] = 1;
            dfs(i, 0, cnt);
        }

    }
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= cnt; i++) {
        if (ans[i].size() > 3) {
            flag = 1;
            break;
        }
    }
    for (int i = 1; i <= cnt; i++) {
        if (ans[i].size() == 2) {
            int k;
            for (k = 1; k <= cnt; k++) {
                if (!vis[k] && ans[k].size() == 1) {
                    vis[k] = 1;
                    ans[i].push_back(ans[k][0]);
                    break;
                }
            }
            if (k == cnt + 1) {
                flag = 1;
                break;
            }
        }
    }
    for (int i = 1; i <= cnt; i++) {
        int cnt_number = 0;
        if (ans[i].size() == 1 && !vis[i]) {
            vis[i] = 1;
            int k;
            for (k = 1; k <= cnt; k++) {
                if (!vis[k] && ans[k].size() == 1) {
                    vis[k] = 1;
                    cnt_number++;
                    ans[i].push_back(ans[k][0]);
                }
                if (cnt_number == 2) {
                    break;
                }
            }
            if (k == cnt + 1) {
                flag = 1;
                break;
            }
        }
    }
    if (flag) {
        printf("-1\n");
    }
    else {
        for (int i = 1; i <= cnt; i++) {
            if (ans[i].size() == 3) {
                printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
            }
        }
    }
    return 0;
}
