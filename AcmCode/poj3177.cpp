#include <cstdio>
#include <string.h>
#include <vector>

#define MAX_NUMBER 5005
#define min(a,b) ((a) > (b)) ? (b) : (a)

using namespace std;

vector<int> path[MAX_NUMBER];
vector<int> bridge[MAX_NUMBER];
int low[MAX_NUMBER], pre[MAX_NUMBER], block_number[MAX_NUMBER], degree[MAX_NUMBER], maps[MAX_NUMBER][MAX_NUMBER];
int dfs_index, block_index, point_number, edge_number;

void dfs(int cnt_point, int father) {
    low[cnt_point] = pre[cnt_point] = ++dfs_index;
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!pre[next_point]) {
            dfs(next_point, cnt_point);
            low[cnt_point] = min(low[cnt_point], low[next_point]);
            if (low[next_point] > pre[cnt_point]) {
                bridge[cnt_point].push_back(next_point);
                bridge[next_point].push_back(cnt_point);
            }
        }
        else if (next_point != father) {
            low[cnt_point] = min(low[cnt_point], pre[next_point]);
        }
    }
}

void getBlock(int cnt_point) {
    block_number[cnt_point] = block_index;
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int is_bridge = 0;
        int next_point = path[cnt_point][i];
        for (int j = 0; j < bridge[cnt_point].size(); j++) {
            if (bridge[cnt_point][j] == next_point) {
                is_bridge = 1;
                break;
            }
        }
        if (!is_bridge && !block_number[next_point]) {
            getBlock(next_point);
        }
    }
}

void solve() {
    memset(block_number, 0, sizeof(block_number));
    memset(degree, 0, sizeof(degree));
    memset(low, 0, sizeof(low));
    dfs_index = block_index = 0;
    for (int i = 1; i <= point_number; i++) {
        if (!pre[i]) {
            dfs(i, -1);
        }
    }
    for (int i = 1; i <= point_number; i++) {
        if (!block_number[i]) {
            block_index++;
            getBlock(i);
        }
    }
}


int main() {

    scanf("%d%d", &point_number, &edge_number);
    for (int i = 1; i <= edge_number; i++) {
        int point_1, point_2;
        scanf("%d%d", &point_1, &point_2);
        if (maps[point_1][point_2]) {
            continue;
        }
        path[point_1].push_back(point_2);
        path[point_2].push_back(point_1);
        maps[point_1][point_2] = 1;
    }
    solve();
    memset(degree, 0, sizeof(degree));
    for (int i = 1; i <= point_number; i++) {
        for (int j = 0; j < path[i].size(); j++) {
            if (block_number[i] != block_number[path[i][j]]) {
                degree[block_number[i]]++;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= block_index; i++) {
        if (degree[i] == 1) {
            ans++;
        }
    }
    printf("%d\n", (ans + 1) / 2);
    return 0;
}
