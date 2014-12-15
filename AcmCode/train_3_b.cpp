#include <cstdio>
#include <string.h>


const int MAX_NUMBER = 125;

int maps[MAX_NUMBER][MAX_NUMBER];
int state[MAX_NUMBER], previous_node[MAX_NUMBER];
int point_number, edge_number;

int hungry(int cnt_point) {
    for (int i = 1; i <= point_number; i++) {
        if (maps[cnt_point][i] && !state[i]) {
            state[i] = 1;
            if (!previous_node[i] || hungry(previous_node[i])) {
                previous_node[i] = cnt_point;
                return 1;
            }
        }
    }
    return 0;
}

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(maps, 0, sizeof(maps));
        memset(state, 0, sizeof(state));
        memset(previous_node, 0, sizeof(previous_node));
        scanf("%d%d", &point_number, &edge_number);
        for (int i = 1; i <= edge_number; i++) {
            int start, end;
            scanf("%d%d", &start, &end);
            maps[start][end] = 1;
        }
        int ans = 0;
        for (int i = 1; i <= point_number; i++) {
            memset(state, 0, sizeof(state));
            if (hungry(i)) {
                ans++;
            }
        }
        ans = point_number - ans;
        printf("%d\n", ans);
    }
    return 0;
}
