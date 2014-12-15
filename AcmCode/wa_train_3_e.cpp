#include <string.h>
#include <cstdio>
#include <vector>

using namespace std;

#define min(a,b) ((a) > (b)) ? (b) : (a)

const int MAX_POINT = 10020;

vector<int> path[MAX_POINT];
int low[MAX_POINT], pre[MAX_POINT], block[MAX_POINT];
int point_number, edge_number, dfs_index, number;

void dfs(int cnt_point, int father) {
    low[cnt_point] = pre[cnt_point] = ++dfs_index;
    int child = 0;
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
        block[cnt_point] = 1;
    }
}

void findBcc() {
    memset(low, 0, sizeof(low));
    memset(pre, 0, sizeof(pre));
    dfs_index = 0;
    number = 0;
    for (int i = 0; i < point_number; i++) {
        block[i] = 1;
    }
    for (int i = 0; i < point_number; i++) {
        if (!pre[i]) {
            dfs(i, -1);
            number++;
        }
    }
}

int main() {

    while (scanf("%d%d", &point_number, &edge_number) != EOF) {
        if (!point_number && !edge_number) {
            break;
        }
        if (edge_number == 0) {
            printf("%d\n", point_number - 1);
            continue;
        }
        for (int i = 0; i < point_number; i++) {
            path[i].clear();
        }
        for (int i = 1; i <= edge_number; i++) {
            int start, end;
            scanf("%d%d", &start, &end);
            path[start].push_back(end);
            path[end].push_back(start);
        }
        findBcc();
        int ans;
        int max_number = 1;
        for (int i = 0; i < point_number; i++) {
            if (block[i] > max_number) {
                max_number = block[i];
            }
        }
        ans = max_number + number - 1;
        printf("%d\n", ans);
    }
    return 0;
}
