#include <string.h>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_NUMBER = 10020;
int low[MAX_NUMBER], pre[MAX_NUMBER], block[MAX_NUMBER];
int dfs_index, point_number, edge_number, block_number;

vector<int> path[MAX_NUMBER];

void dfs(int cnt_point, int father) {
    int child = 0;
    low[cnt_point] = pre[cnt_point] = ++dfs_index;
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!pre[next_point]) {
            child++;
            dfs(next_point, cnt_point);
            low[cnt_point] = min(low[cnt_point], low[next_point]);
            if (low[next_point] >= pre[cnt_point]) {
                block[cnt_point]++;
            }
        }
        else if (pre[next_point] < pre[cnt_point] && next_point != father) {
            low[cnt_point] = min(low[cnt_point], pre[next_point]);
        }
    }
    if (father < 0 && child == 1) {
        block[cnt_point] = 0;
    }
}

void findBcc() {
    memset(low, 0, sizeof(low));
    memset(pre, 0, sizeof(pre));
    memset(block, 0, sizeof(block));
    dfs_index = block_number = 0;
    for (int i = 0; i < point_number; i++) {
        if (!pre[i]) {
            dfs(i, -1);
            block_number++;
        }
    }
}

int main() {

    while (scanf("%d%d", &point_number, &edge_number) != EOF) {
        if (!point_number && !edge_number) {
            break;
        }
        if (!edge_number) {
            printf("%d\n", point_number - 1);
            continue;
        }
        for (int i = 0; i < point_number; i++) {
            path[i].clear();
        }
        for (int i = 0; i < edge_number; i++) {
            int start, end;
            scanf("%d%d", &start, &end);
            path[start].push_back(end);
            path[end].push_back(start);
        }
        findBcc();
        int max_number = 1;
        for (int i = 0; i < point_number; i++) {
            if (block[i] > max_number) {
                max_number = block[i];
            }
        }
        int ans = block_number + max_number - 1;
        printf("%d\n", ans);
    }
    return 0;
}
