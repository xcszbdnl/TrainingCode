#include <string.h>
#include <cstdio>
#include <stack>
#include <vector>

const int MAX_POINT = 105;

using namespace std;

#define min(a, b) ((a) > (b)) ? (b) : (a)
#define max(a, b) ((a) > (b)) ? (a) : (b)

vector<int> path[MAX_POINT];
stack<int> cnt_stack;
int low[MAX_POINT], pre[MAX_POINT], in[MAX_POINT], out[MAX_POINT], block_number[MAX_POINT];
int dfs_index, point_number, block_index;


void dfs(int cnt_point) {
    low[cnt_point] = pre[cnt_point] = ++dfs_index;
    cnt_stack.push(cnt_point);
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!pre[next_point]) {
            dfs(next_point);
            low[cnt_point] = min(low[cnt_point], low[next_point]);
        }
        else if (!block_number[next_point]){
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
    memset(low, 0, sizeof(low));
    memset(pre, 0, sizeof(pre));
    memset(block_number, 0, sizeof(block_number));
    dfs_index = block_index = 0;
    for (int i = 1; i <= point_number; i++) {
        if (!pre[i]) {
            dfs(i);
        }
    }
}

int main() {

    scanf("%d", &point_number);
    for (int i = 1; i <= point_number; i++) {
        int next_point;
        while (scanf("%d", &next_point) == 1) {
            if (next_point == 0) {
                break;
            }
            path[i].push_back(next_point);
        }
    }
    findBcc();
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    for (int i = 1; i <= point_number; i++) {
        for (int j = 0; j < path[i].size(); j++) {
            int next_point = path[i][j];
            if (block_number[i] != block_number[next_point]) {
                out[block_number[i]]++;
                in[block_number[next_point]]++;
            }
        }
    }
    int in_number = 0;
    int out_number = 0;
    for (int i = 1; i <= block_index; i++) {
        if (in[i] == 0) {
            in_number++;
        }
        else if (out[i] == 0){
            out_number++;
        }
    }
    int max_number = max(in_number, out_number);
    if (block_index == 1) {
        in_number = 1;
        max_number = 0;
    }
    printf("%d\n", in_number);
    printf("%d\n", max_number);
    return 0;
}
