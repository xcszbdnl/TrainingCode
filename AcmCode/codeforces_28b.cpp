#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int MAX_NUMBER = 105;
int n;
int vis[MAX_NUMBER];
int state[MAX_NUMBER], favorite[MAX_NUMBER];
vector<int> path_1[MAX_NUMBER];
vector<int> path_2[MAX_NUMBER];
vector<int> cycle[MAX_NUMBER];
vector<int> state_cycle[MAX_NUMBER];
int state_number, cycle_number;

void dfs1(int cnt_point) {
    for (int i = 0; i < path_1[cnt_point].size(); i++) {
        int next_point = path_1[cnt_point][i];
        if (!vis[next_point]) {
            vis[next_point] = 1;
            cycle[cycle_number].push_back(next_point);
            dfs1(next_point);
        }
    }
}

void dfs2(int cnt_point) {
    for (int i = 0; i < path_2[cnt_point].size(); i++) {
        int next_point = path_2[cnt_point][i];
        if (!vis[next_point]) {
            vis[next_point] = 1;
            state_cycle[state_number].push_back(next_point);
            dfs2(next_point);
        }
    }
}

int main() {

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &state[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &favorite[i]);
    }
    state_number = 0;
    cycle_number = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) {
        int next_1 = i + favorite[i];
        int next_2 = i - favorite[i];
        if (next_1 <= n) {
            path_1[i].push_back(next_1);
            path_1[next_1].push_back(i);
        }
        if (next_2 >= 1) {
            path_1[i].push_back(next_2);
            path_1[next_2].push_back(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            cycle_number++;
            cycle[cycle_number].push_back(i);
            dfs1(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        int next_1 = i + favorite[i];
        int next_2 = i - favorite[i];
        if (next_1 <= n) {
            path_2[state[i]].push_back(state[next_1]);
            path_2[state[next_1]].push_back(state[i]);            
        }
        if (next_2 >= 1) {
            path_2[state[i]].push_back(state[next_2]);
            path_2[state[next_2]].push_back(state[i]);
            
        }
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            state_number++;
            state_cycle[state_number].push_back(i);
            dfs2(i);
        }
    }
    if (cycle_number != state_number) {
        printf("NO\n");
    }
    else {
        for (int i = 1; i <= cycle_number; i++) {
            sort(cycle[i].begin(), cycle[i].end());
            sort(state_cycle[i].begin(), state_cycle[i].end());
        }
        int flag = 0;
        for (int i = 1; i <= cycle_number && !flag; i++) {
            if (cycle[i].size() != state_cycle[i].size()) {
                flag = 1;
                break;
            }
            for (int j = 0; j < cycle[i].size(); i++) {
                if (cycle[i][j] != state_cycle[i][j]) {
                    flag = 1;
                    break;
                }
                if (cycle[i].size() == 1) {
                    if (state[cycle[i][j]] != cycle[i][j]) {
                        flag = 1;
                        break;
                    }
                }
            }
        }
        if (flag) {
            printf("NO\n");
        }
        else {
            printf("YES\n");
        }
    }
    return 0;
}
