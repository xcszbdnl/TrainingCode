#include <cstdio>
#include <cstring>

const int MAX_NUMBER = 1007;

struct Point {
    int x, y;
};

struct Point que[MAX_NUMBER];
int left_x, left_y, point_number;
int vis[107][107], maps[107][107];
int step[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
char name_step[5] = "RTLB";
char str[MAX_NUMBER][10];

void bfs() {
    int front = 0;
    int rear = 1;
    que[front].x = left_x;
    que[front].y = left_y;
    int number = 1;
    vis[left_x][left_y] = 1;
    while (front < rear) {
        struct Point cnt = que[front];
        int cnt_x = cnt.x;
        int cnt_y = cnt.y;
        if (number == point_number) {
            printf(".\n");
            return ;
        }
        for (int i = 0; i < 4; i++) {
            int next_x = cnt_x + step[i][0];
            int next_y = cnt_y + step[i][1];
            if (!vis[next_x][next_y] && maps[next_x][next_y]) {
                printf("%c", name_step[i]);
                vis[next_x][next_y] = 1;
                que[rear].x = next_x;
                que[rear].y = next_y;
                rear++;
            }
        }
        printf(",\n");
        number++;
        front++;
    }
}

void bfs2() {
    int front = 0;
    int rear = 1;
    que[front].x = left_x;
    que[front].y = left_y;
    while (front < rear) {
        struct Point cnt = que[front];
        int cnt_x = cnt.x;
        int cnt_y = cnt.y;
        char temp[20];
        scanf("%s", temp);
        if (temp[0] == '.') {
            break;
        }
        for (int i = 0; temp[i] != ','; i++) {
            for (int j = 0; j < 4; j++) {
                if (temp[i] == name_step[j]) {
                    int next_x = cnt_x + step[j][0];
                    int next_y = cnt_y + step[j][1];
                    maps[next_x][next_y] = 1;
                    que[rear].x = next_x;
                    que[rear].y = next_y;
                    rear++;
                    break;
                }
            }
        }
        front++;
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    char temp[20];
    gets(temp);
    int flag = 0;
    for (int i = 0; temp[i]; i++) {
        if (temp[i] == ' ') {
            flag = 1;
        }
    }
    if (!flag) {
        sscanf(temp, "%d", &point_number);
        memset(vis, 0, sizeof(vis));
        memset(maps, 0, sizeof(maps));
        for (int i = 1; i <= point_number; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (i == 1) {
                left_x = x;
                left_y = y;
            }
            maps[x][y] = 1;
        }
        printf("%d %d\n", left_x, left_y);
        bfs();
    }
    else {
        sscanf(temp, "%d %d", &left_x, &left_y);
        point_number = 1;
        memset(maps, 0, sizeof(maps));
        maps[left_x][left_y] = 1;
        bfs2();
        int ans = 0;
        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                if (maps[i][j]) {
                    ans++;
                }
            }
        }
        printf("%d\n", ans);
        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                if (maps[i][j]) {
                    printf("%d %d\n", i, j);
                }
            }
        }
    }
    return 0;
}
