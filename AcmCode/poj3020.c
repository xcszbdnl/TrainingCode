#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 1000
int map[MAX_NUMBER][MAX_NUMBER];
int edge[MAX_NUMBER][MAX_NUMBER];
int state[MAX_NUMBER];
int previous_node[MAX_NUMBER];
int row, column;
int neighbour[4][2] = {1,0,-1,0,0,1,0,-1};
int point_number;

int hungary(int start_point) {
    int i;
    for (i = 1; i <= point_number; i++) {
        if (edge[start_point][i] && !state[i]) {
            state[i] = 1;
            if (!previous_node[i] || hungary(previous_node[i])) {
                previous_node[i] = start_point;
                return 1;
            }
        }
    }
    return 0;
}

int main() {

    int test_case, i, j, k;
    int neighbour_x, neighbour_y, ans;
    char input_map[MAX_NUMBER];
    scanf("%d", &test_case);
    while (test_case--) {
        point_number = 0;
        ans = 0;
        scanf("%d%d", &row, &column);
        memset(map, 0, sizeof(map));
        memset(previous_node, 0, sizeof(previous_node));
        memset(edge, 0, sizeof(edge));
        for (i = 1; i <= row; i++) {
            scanf("%s", input_map);
            for (j = 1; j <= column; j++) {
                if (input_map[j - 1] == '*') {
                    map[i][j] = ++point_number;
                }
                else {
                    map[i][j] = 0;
                }
            }
        }
        for (i = 1; i <= row; i++) {
            for (j = 1; j <= column; j++) {
                if (map[i][j]) {
                    for (k = 0; k < 4; k++) {
                        neighbour_x = i + neighbour[k][0];
                        neighbour_y = j + neighbour[k][1];
                        if (map[neighbour_x][neighbour_y]) {
                            edge[map[i][j]][map[neighbour_x][neighbour_y]] = 1;
                        }
                    }
                }
            }
        }
        for (i = 1; i <= point_number; i++) {
            memset(state, 0, sizeof(state));
            if (hungary(i)) {
                ans++;
            }
        }
        printf("%d\n", point_number - ans / 2);
    }
}

