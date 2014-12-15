#include <cstdio>
#include <string.h>


const int MAX_NUMBER = 33;
const int MAX_POINT = MAX_NUMBER * MAX_NUMBER;

int maps[MAX_POINT][MAX_POINT];
int hole_location[MAX_POINT][MAX_POINT];
int state[MAX_POINT], previous_node[MAX_POINT];
int step[4][3] = {{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}};
int row, column, hole, point_number;

void buildGraph() {
    for (int i = 1; i <= row * column; i++) {
        int x = (i - 1) / column;
        x += 1;
        int y = (i - 1) % column;
        y += 1;
        if (hole_location[x][y] == 1) {
            continue;
        }
        for (int j = 0; j < 4; j++) {
            int next_x = x + step[j][0];
            int next_y = y + step[j][1];
            int next_point = i + step[j][2];
            if (next_x >= 1 && next_x <= row && next_y >= 1 && next_y <= column) {
                if (!hole_location[next_x][next_y]) {
                    maps[i][next_point] = 1;
                }
            }
        }
    }
}

int hungry(int cnt_point) {
    for (int i = 1; i <= row * column; i++) {
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

    scanf("%d%d%d", &row, &column, &hole);
    for (int i = 1; i <= hole; i++) {
        int x, y;
        scanf("%d%d", &y, &x);
        hole_location[x][y] = 1;
    }
    int ans;
    if ((row * column - hole) % 2 == 1) {
        printf("NO\n");     
        return 0;
    }
    else {
        point_number = row * column / 2;
        step[0][2] = -column, step[1][2] = column, step[2][2] = -1, step[3][2] = 1;
        buildGraph();
        ans = 0;
        for (int i = 1; i <= row * column; i++) {
            memset(state, 0, sizeof(state));
            int cnt_x = (i - 1) / column;
            cnt_x++;
            int cnt_y = (i - 1) % column;
            cnt_y++;
            if (!hole_location[cnt_x][cnt_y] && hungry(i)) {
                ans++;
            }
        }
    }
    ans /= 2;
    if (point_number - hole / 2 == ans) {
        printf("YES\n");
    }
    else {
        printf("NO\n");        
    }
    return 0;
}

