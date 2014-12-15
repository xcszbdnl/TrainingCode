#include <cstdio>
#include <string.h>
#include <vector>
#include <stack>

#define MAX_POINT 10005
#define min(a,b) ((a) > (b)) ? (b) : (a)
using namespace std;

vector<int> maps[MAX_POINT];
stack<int> s;
int low[MAX_POINT], pre[MAX_POINT], block_number[MAX_POINT], degree[MAX_POINT];
int dfs_index, block_index, point_number, edge_number;

void dfs(int cnt_point) {
    pre[cnt_point] = low[cnt_point] = ++dfs_index;
    s.push(cnt_point);
    for (int i = 0; i < maps[cnt_point].size(); i++) {
        int next_point = maps[cnt_point][i];
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
            int x = s.top();
            s.pop();
            block_number[x] = block_index;
            if (x == cnt_point) {
                break;
            }
        }
    }
}

void findBcc() {
    dfs_index = block_index = 0;
    memset(pre, 0, sizeof(pre));
    memset(low, 0, sizeof(low));
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
        int point_1, point_2;
        scanf("%d%d", &point_1, &point_2);
        maps[point_1].push_back(point_2);
    }
    findBcc();
    memset(degree, 0, sizeof(degree));
    for (int i = 1; i <= point_number; i++) {
        for (int j = 0; j < maps[i].size(); j++) {
            int next_point = maps[i][j];
            if (block_number[i] != block_number[next_point]) {
                degree[block_number[i]]++;
            }
        }
    }
    int zero_number = 0;
    int zero_degree;
    for (int i = 1; i <= block_index; i++) {
        if (degree[i] == 0) {
            zero_degree++;
            zero_degree = i;
        }
    }
    int ans = 0;
    if (zero_degree == 1) {
        for (int i = 1; i <= point_number; i++) {
            if (block_number[i] == zero_degree) {
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
