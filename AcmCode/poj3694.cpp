#include <cstdio>
#include <string.h>
#include <vector>

#define MAX_NUMBER 100005
#define min(a,b) ((a) > (b)) ? (b) : (a)

using namespace std;
vector<int> path[MAX_NUMBER];
int low[MAX_NUMBER], pre[MAX_NUMBER], is_bridge[MAX_NUMBER], father[MAX_NUMBER];
int point_number, edge_number, dfs_index, bridge_number, query_number;

void dfs(int cnt_point, int cnt_father) {
    low[cnt_point] = pre[cnt_point] = ++dfs_index;
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!pre[next_point]) {
            father[next_point] = cnt_point;
            dfs(next_point, cnt_point);
            low[cnt_point] = min(low[cnt_point], low[next_point]);
            if (low[next_point] > pre[cnt_point]) {
                is_bridge[next_point] = 1;
                bridge_number++;
            }
        }
        else if (next_point != cnt_father) {
            low[cnt_point] = min(low[cnt_point], pre[next_point]);
        }
    }
}

void findBcc() {
    memset(low, 0, sizeof(low));
    memset(pre, 0, sizeof(pre));
    dfs_index = 0;
    for (int i = 1; i <= point_number; i++) {
        father[i] = i;
    }
    for (int i = 1; i <= point_number; i++) {
        if (!pre[i]) {
            dfs(i, -1);
        }
    }
}

void query(int point_1, int point_2) {
    while (pre[point_1] > pre[point_2]) {
        if (is_bridge[point_1]) {
            bridge_number--;
            is_bridge[point_1] = 0;
        }
        point_1 = father[point_1];
    }
    while (pre[point_2] > pre[point_1]) {
        if (is_bridge[point_2]) {
            bridge_number--;
            is_bridge[point_2] = 0;
        }
        point_2 = father[point_2];
    }
    while (point_1 != point_2) {
        if (is_bridge[point_1]) {
            bridge_number--;
            is_bridge[point_1] = 0;
        }
        if (is_bridge[point_2]) {
            bridge_number--;
            is_bridge[point_2] = 0;
        }
        point_1 = father[point_1];
        point_2 = father[point_2];
    }
}



int main() {

    int case_number = 1;
    while (scanf("%d%d", &point_number, &edge_number) != EOF) {
        if (!point_number && !edge_number) {
            break;
        }
        for (int i = 1; i <= edge_number; i++) {
            int point_1, point_2;
            scanf("%d%d", &point_1, &point_2);
            path[point_1].push_back(point_2);
            path[point_2].push_back(point_1);
        }
        bridge_number = 0;
        memset(is_bridge, 0, sizeof(is_bridge));
        findBcc();
        scanf("%d", &query_number);
        printf("Case %d:\n", case_number);
        case_number++;
        for (int i = 1; i <= query_number; i++) {
            int point_1, point_2;
            scanf("%d%d", &point_1, &point_2);
            query(point_1, point_2);
            printf("%d\n", bridge_number);
        }
    }
    return 0;
}
