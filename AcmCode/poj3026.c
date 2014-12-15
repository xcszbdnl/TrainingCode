#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 110
#define INF 5000

char original_map[MAX_NUMBER][MAX_NUMBER];
int map[MAX_NUMBER][MAX_NUMBER];
int original_distance[MAX_NUMBER][MAX_NUMBER];
int distance[MAX_NUMBER][MAX_NUMBER];
int point_number, row, column;
int steps[4][2] = {0,-1,0,1,-1,0,1,0};
int lowest[MAX_NUMBER];
struct Location {
    int x;
    int y;
};

struct Location location[MAX_NUMBER * MAX_NUMBER];
int vis[MAX_NUMBER][MAX_NUMBER];

void bfs(int source_x, int source_y) {
    int x, y, next_x, next_y;
    int i, source_number, next_number;
    int front, rear;    
    memset(vis, 0, sizeof(vis));
    memset(original_distance, 0, sizeof(original_distance));
    front = 0;
    rear = 1;
    location[front].x = source_x;
    location[front].y = source_y;
    vis[source_x][source_y] = 1;
    while (front < rear) {
        x = location[front].x;
        y = location[front].y;
        if (map[x][y] > 0) {
            source_number = map[source_x][source_y];
            next_number = map[x][y];
            distance[source_number][next_number] = original_distance[x][y];
        }
        for (i = 0; i < 4; i++) {
            next_x = x + steps[i][0];
            next_y = y + steps[i][1];
            if (next_x >= 1 && next_x <= row && next_y >= 1 && next_y <= column) {
                if (!vis[next_x][next_y] && original_map[next_x][next_y - 1] != '#') {
                    location[rear].x = next_x;
                    location[rear].y = next_y;
                    vis[next_x][next_y] = 1;
                    original_distance[next_x][next_y] = original_distance[x][y] + 1;
                    rear++;
                }
            }
        }
        front++;
    }
}

int prim() {
    int visited[MAX_NUMBER];
    int i, j;
    int min, sum, currenct_point;
    sum = 0;
    memset(visited, 0, sizeof(visited));
    for (i = 1; i <= point_number; i++) {
        lowest[i] = distance[1][i];
    }
    visited[1] = 1;
    for (i = 1; i < point_number; i++) {
        min = INF;
        for (j = 1; j <= point_number; j++) {
            if (!visited[j] && min > lowest[j]) {
                min = lowest[j];
                currenct_point = j;
            }
        }
        sum += lowest[currenct_point];
        visited[currenct_point] = 1;
        for (j = 1; j <= point_number; j++) {
            if (!visited[j] && lowest[j] > distance[currenct_point][j]) {
                lowest[j] = distance[currenct_point][j];
            }
        }
    }
    return sum;
}

int main() {

    int test_case;
    int i, j;
    char temp[MAX_NUMBER];
    scanf("%d", &test_case);
    while (test_case--) {
        memset(map, 0, sizeof(map));
        scanf("%d%d", &column, &row);
        gets(temp);
        point_number = 0;
        for (i = 1; i <= row; i++) {
            gets(original_map[i]);
            for (j = 0; j < column ;j++) {
                if (original_map[i][j] == 'S' || original_map[i][j] == 'A') {
                    map[i][j + 1] = ++point_number;
                }
            }
        }
        for (i = 1; i<= row; i++) {
            for (j = 1; j <= column; j++) {
                if (map[i][j]) {
                    bfs(i ,j);
                }
            }
        }
        printf("%d\n", prim());
    }
}
