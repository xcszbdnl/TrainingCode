#include <cstdio>
#include <string.h>
#include <vector>
#include <stack>

#define MAX_NUMBER 105
#define min(a,b) ((a) > (b)) ? (b) : (a)
#define max(a,b) ((a) > (b)) ? (a) : (b)

using namespace std;

vector<int> path[MAX_NUMBER];
stack<int> s;
int low[MAX_NUMBER], pre[MAX_NUMBER], block_number[MAX_NUMBER], in[MAX_NUMBER], out[MAX_NUMBER];
int dfs_index, block_index, point_number, edge_number;

void dfs(int cnt_point, int father) {
    low[cnt_point] = pre[cnt_point] = ++dfs_index;
    s.push(cnt_point);
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!pre[next_point]) {
            dfs(next_point, cnt_point);
            low[cnt_point] = min(low[cnt_point], low[next_point]);
        }
        else if (!block_number[next_point]) {
            low[cnt_point] = min(low[cnt_point], pre[next_point]);
        }
    }
    if (low[cnt_point] == pre[cnt_point]) {
        block_index++;
        while (1) {
            int x = s.top();
            s.pop();
            block_number[x] = block_index;
            if (cnt_point == x) {
                break;
            }
        }
    }
    
}

void findBcc() {
    memset(low, 0, sizeof(low));
    memset(pre, 0, sizeof(pre));
    memset(block_number, 0, sizeof(block_number));
    for (int i = 1; i <= point_number; i++) {
        if (!pre[i]) {
            dfs(i, -1);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &point_number);
    for (int i = 1; i <= point_number; i++) {
        int point_1;
        while (scanf("%d", &point_1) != EOF) {
            if (!point_1) {
                break;
            }
            path[i].push_back(point_1);
        }
    }
    findBcc();
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    for (int i = 1; i <= point_number; i++) {
        for (int j = 0; j < path[i].size(); j++) {
            if (block_number[i] != block_number[path[i][j]]) {
                in[block_number[path[i][j]]]++;
                out[block_number[i]]++;
            }
        }
    }
    int zero_in, zero_out;
    zero_in = zero_out = 0;
    for (int i = 1; i <= block_index; i++) {
        if (in[i] == 0) {
            zero_in++;
        }
        if (out[i] == 0) {
            zero_out++;
        }
    }
    if (block_index != 1) {
        printf("%d\n", zero_in);
        int ans = max(zero_in, zero_out);
        printf("%d\n", ans);
    }
    else {
        printf("1\n0\n");
    }
    return 0;
}
