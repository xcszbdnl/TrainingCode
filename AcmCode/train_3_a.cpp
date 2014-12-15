#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 505;

int maps[MAX_NUMBER][MAX_NUMBER];
int state[MAX_NUMBER], previous_node[MAX_NUMBER];
int point_number, row;

int hungry(int cnt_point) {
    for (int i = 1; i <= row; i++) {
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

    scanf("%d%d", &row, &point_number);
    memset(maps, 0, sizeof(maps));
    for (int i = 1; i <= point_number; i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        maps[x][y] = 1;
    }
    int ans = 0;
    for (int i = 1; i <= row; i++) {
        memset(state, 0, sizeof(state));
        if (hungry(i)) {
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
