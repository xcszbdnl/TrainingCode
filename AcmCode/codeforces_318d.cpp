#include <cstdio>
#include <string.h>


const int MAX_NUMBER = 1000;
const int LENGTH = MAX_NUMBER * 100;

/*struct Point {
    int x;
    int y;
};
struct Point queue[LENGTH];

int vis[MAX_NUMBER * 2 + 10][MAX_NUMBER * 2 + 10];
*/
int steps[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
int n, query_number;
int number[MAX_NUMBER * 2 + 10][MAX_NUMBER * 2 + 10];

/*void bfs() {
    int front = 0;
    int rear = 1;
    memset(number, 0, sizeof(number));
    queue[front].x = 1000;
    queue[front].y = 1000;
    number[1000][1000] = n;
    while (front < rear) {
        struct Point cnt_point = queue[front];
        vis[cnt_point.x][cnt_point.y] = 1;
        for (int i = 0; i < 4; i++) {
            int next_x = cnt_point.x + steps[i][0];
            int next_y = cnt_point.y + steps[i][1];
            number[next_x][next_y] += number[cnt_point.x][cnt_point.y] / 4;
            if (number[next_x][next_y] >= 4 && !vis[next_x][next_y]) {
                vis[next_x][next_y] = 1;
                queue[rear].x = next_x;
                queue[rear].y = next_y;
                rear++;
                rear %= LENGTH;
            }
        }
        number[cnt_point.x][cnt_point.y] %= 4;
        vis[cnt_point.x][cnt_point.y] = 0;
        front++;
        front %= LENGTH;
    }
}
*/

void dfs(int x, int y) {
    if (number[x][y] < 4) {
        return ;
    }
    int temp = number[x][y] / 4;
    number[x][y] %= 4;
    for (int i = 0; i < 4; i++) {
        int next_x = x + steps[i][0];
        int next_y = y + steps[i][1];
        number[next_x][next_y] += temp;
        dfs(next_x, next_y);
    }

}

int main() {

    scanf("%d%d", &n, &query_number);
    number[1000][1000] = n;
    dfs(1000, 1000);
    for (int i = 1; i <= query_number; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x += 1000;
        y += 1000;        
        if (x > 0 && x < 2000 && y > 0 && y < 2000) {
            printf("%d\n", number[x][y]);
        }
        else {
            printf("0\n");
        }
    }
    return 0;
}
