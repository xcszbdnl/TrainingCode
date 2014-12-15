#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 300

int map[MAX_NUMBER][MAX_NUMBER];
int vis[MAX_NUMBER], previous_node[MAX_NUMBER];
int cows_number, stall_number;

int hungary(int node_number) {
    int i;
    for (i = 1; i <= stall_number; i++) {
        if (map[node_number][i] && !vis[i]) {
            vis[i] = 1;
            if (!previous_node[i] || hungary(previous_node[i])) {
                previous_node[i] = node_number;
                return 1;
            }
        }
    }
    return 0;
}

int main() {

    int i, j, preference_number, stall, ans;
    while (scanf("%d%d", &cows_number, &stall_number) != EOF) {
        memset(map, 0, sizeof(map));
        memset(previous_node, 0 , sizeof(previous_node));
        ans = 0;
        for (i = 1; i <= cows_number; i++) {
            scanf("%d", &preference_number);
            for (j = 1; j <= preference_number; j++) {
                scanf("%d", &stall);
                map[i][stall] = 1;
            }
        }
        for (i = 1; i <= cows_number; i++) {
            memset(vis, 0 ,sizeof(vis));
            if (hungary(i)) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
