#include <cstdio>
#include <string.h>
#include <vector>
#include <stack>


using namespace std;

const int MAX_POINT = 10005;

#define min(a,b) ((a) > (b)) ? (b) : (a)
vector<int> path[MAX_POINT];
stack<int> cnt_stack;
int low[MAX_POINT], pre[MAX_POINT], block_number[MAX_POINT], out[MAX_POINT];
int dfs_index, block_index;
int point_number, edge_number;

void dfs(int cnt_point) {
    pre[cnt_point] = low[cnt_point] = ++dfs_index;
    cnt_stack.push(cnt_point);
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!pre[next_point]) {
            dfs(next_point);
            low[cnt_point] = min(low[cnt_point], low[next_point]);
        }
        else if (!block_number[next_point]) {
            low[cnt_point] = min(low[cnt_point], pre[next_point]);
        }
    }
    if (low[cnt_point] == pre[cnt_point]) {
        block_index++;
        while (1) {
            int node = cnt_stack.top();
            cnt_stack.pop();
            block_number[node] = block_index;
            if (node == cnt_point) {
                break;
            }
        }
    }
}

void findBcc() {
    dfs_index = block_index = 0;
    memset(low, 0, sizeof(low));
    memset(pre, 0, sizeof(pre));
    memset(block_number, 0, sizeof(block_number));
    for (int i = 1; i <= point_number; i++) {
        if (!pre[i]) {
            dfs(i);
        }
    }
}

int main() {

    scanf("%d%d", &point_number, &edge_number);
    for (int i = 1; i <= edge_number; i++) {
        int start, end;
        scanf("%d%d", &start, &end);
        path[start].push_back(end);
    }
    findBcc();
    for (int i = 1; i <= point_number; i++) {
        for (int j = 0; j < path[i].size(); j++) {
            int next_point = path[i][j];
            if (block_number[i] != block_number[next_point]) {
                out[block_number[i]]++;
            }
        }
    }
    int zero_degree = 0;
    int zero_number;
    for (int i = 1; i <= block_index; i++) {
        if (out[i] == 0) {
            zero_degree++;
            zero_number = i;
        }
    }
    int ans = 0;
    if (zero_degree == 1) {
        for (int i = 1; i <= point_number; i++) {
            if (block_number[i] == zero_number) {
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
