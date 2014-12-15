#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1004;
const int INF = 100000000;


char maps[MAX_NUMBER][MAX_NUMBER];

struct Point {
    int x;
    int y;
};


struct Point queue[MAX_NUMBER * MAX_NUMBER];
int row, column;
int vis[MAX_NUMBER][MAX_NUMBER];
int steps[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
int dist[MAX_NUMBER][MAX_NUMBER];
int ans, start_x, start_y;
int min_step;
int end_x, end_y;

void bfs() {
    int front = 0;
    int rear = 1;
    queue[front].x = end_x;
    queue[front].y = end_y;
    dist[end_x][end_y] = 0;
    vis[end_x][end_y] = 1;
    while (front < rear) {
        struct Point cnt_point = queue[front];
        if (cnt_point.x == start_x && cnt_point.y == start_y) {
            min_step = dist[start_x][start_y];
        }
        int next_x, next_y;
        for (int i = 0; i < 4; i++) {
            next_x = cnt_point.x + steps[i][0];
            next_y = cnt_point.y + steps[i][1];
            if (next_x >= 0 && next_x < row && next_y >= 0 && next_y < column) {
                if (maps[next_x][next_y] != 'T' && !vis[next_x][next_y]) {
                    vis[next_x][next_y] = 1;
                    dist[next_x][next_y] = dist[cnt_point.x][cnt_point.y] + 1;
                    struct Point next_point;
                    next_point.x = next_x;
                    next_point.y = next_y;
                    queue[rear] = next_point;
                    rear++;
                }
            }
        }
        front++;
    }
}

int main() {

    scanf("%d%d", &row, &column);
    for (int i = 0; i < row; i++) {
        scanf("%s", maps[i]);
        for (int j = 0; j < column; j++) {
            if (maps[i][j] == 'E') {
                end_x = i;
                end_y = j;
            }
            else if (maps[i][j] == 'S') {
                start_x = i;
                start_y = j;
            }
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            dist[i][j] = INF;
        }
    }
    bfs();
    ans = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (maps[i][j] >= '1' && maps[i][j] <= '9') {
                if (dist[i][j] <= min_step) {
                    //                    printf("%d\n", dist[i][j]);
                    ans += maps[i][j] - '0';
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
