#include <cstdio>
#include <vector>
#include <stack>
#include <string.h>

#define MAX_NUMBER 1005
#define min(a,b) ((a) > (b)) ? (b) : (a)

using namespace std;
struct Edge {
    int start;
    int end;
};

stack<Edge> edge;
int low[MAX_NUMBER], pre[MAX_NUMBER], block_number[MAX_NUMBER];
vector<int> relation[MAX_NUMBER], block[MAX_NUMBER];
int original_map[MAX_NUMBER][MAX_NUMBER], is_cut[MAX_NUMBER], color[MAX_NUMBER], odd[MAX_NUMBER];
int point_number, edge_number, dfs_index, bcc_cnt;

void dfs(int cnt_point, int father) {
    int child = 0;
    low[cnt_point] = pre[cnt_point] = ++dfs_index;
    for (int i = 0; i < relation[cnt_point].size(); i++) {
        int next_point = relation[cnt_point][i];
        Edge e;
        e.start = cnt_point;
        e.end = next_point;
        if (!pre[next_point]) {
            edge.push(e);
            child++;
            dfs(next_point, cnt_point);
            low[cnt_point] = min(low[cnt_point], low[next_point]);
            if (low[next_point] >= pre[cnt_point]) {
                is_cut[cnt_point] = 1;
                bcc_cnt++;
                block[bcc_cnt].clear();
                while (1) {
                    Edge cnt_edge = edge.top();
                    edge.pop();
                    if (block_number[cnt_edge.start] != bcc_cnt) {
                        block[bcc_cnt].push_back(cnt_edge.start);
                        block_number[cnt_edge.start] = bcc_cnt;
                    }
                    if (block_number[cnt_edge.end] != bcc_cnt) {
                        block[bcc_cnt].push_back(cnt_edge.end);
                        block_number[cnt_edge.end] = bcc_cnt;
                    }
                    if (cnt_edge.start == cnt_point && cnt_edge.end == next_point) {
                        break;
                    }
                }
            }
        }
        else if (pre[next_point] < pre[cnt_point] && next_point != father) {
            edge.push(e);
            low[cnt_point] = min(low[cnt_point], pre[next_point]);
        }
    }
    if (father < 0 && child == 1) {
        is_cut[cnt_point] = 0;
    }
}

void findBcc() {
    memset(pre, 0, sizeof(pre));
    memset(low, 0, sizeof(low));
    memset(block_number, 0, sizeof(block_number));
    memset(is_cut, 0, sizeof(is_cut));
    dfs_index = bcc_cnt = 0;
    for (int i = 0; i < point_number; i++) {
        if (!pre[i]) {
            dfs(i, -1);
        }
    }
}

int isBipartite(int cnt_point, int cnt_block) {
    for (int i = 0; i < relation[cnt_point].size(); i++) {
        int next_point = relation[cnt_point][i];
        if (block_number[next_point] != cnt_block) {
            continue;
        }
        if (color[cnt_point] == color[next_point]) {
            return 0;
        }
        if (!color[next_point]) {
            color[next_point] = 3 - color[cnt_point];
            if (!isBipartite(next_point, cnt_block)) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &point_number, &edge_number) != EOF) {
        if (!point_number && !edge_number) {
            break;
        }
        memset(original_map, 0, sizeof(original_map));
        for (int i = 0; i < point_number; i++) {
            relation[i].clear();
        }
        for (int i = 0; i < edge_number; i++) {
            int point_1, point_2;
            scanf("%d%d", &point_1, &point_2);
            point_1--;
            point_2--;
            original_map[point_1][point_2] = original_map[point_2][point_1] = 1;
        }
        for (int i = 0; i < point_number; i++) {
            for (int j = i + 1; j < point_number; j++) {
                if (original_map[i][j] == 0) {
                    relation[i].push_back(j);
                    relation[j].push_back(i);
                }
            }
        }
        findBcc();
        memset(odd, 0, sizeof(odd));
        for (int i = 1; i <= bcc_cnt; i++) {
            memset(color, 0, sizeof(color));
            for (int j = 0; j < block[i].size(); j++) {
                block_number[block[i][j]] = i;
            }
            int cnt_point = block[i][0];
            color[cnt_point] = 1;
            if (!isBipartite(cnt_point, i)) {
                for (int j = 0; j < block[i].size(); j++) {
                    odd[block[i][j]] = 1;
                }
            }
        }
        int ans = point_number;
        for (int i = 0; i < point_number; i++) {
            if (odd[i]) {
                ans--;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
