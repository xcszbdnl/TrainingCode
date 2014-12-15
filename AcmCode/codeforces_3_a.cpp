#include <cstdio>
#include <cstring>

const int maxn = 107;

struct Move {
    int x, y;
    int step, father;
    char pre[5];
};

struct Move que[maxn];
int vis[maxn][maxn];
int steps[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
char s_name[8][5] = {"LD", "L", "LU", "D", "U", "RD", "R", "RU"};
int s_x, s_y, d_x, d_y;

void printAns(int cnt) {
    if (que[cnt].father != -1) {
        printAns(que[cnt].father);
        printf("%s\n", que[cnt].pre);
    }
}

int bfs() {
    int front = 0;
    int rear = 1;
    que[0].x = s_x;
    que[0].y = s_y;
    que[0].step = 0;
    que[0].father = -1;
    vis[s_x][s_y] = 1;
    while (front < rear) {
        struct Move cnt = que[front];
        if (cnt.x == d_x && cnt.y == d_y) {
            return front;
        }
        for (int i = 0; i < 8; i++) {
            int next_x = cnt.x + steps[i][0];
            int next_y = cnt.y + steps[i][1];
            if (next_x >= 1 && next_x <= 8 && next_y >= 1 && next_y <= 8 && !vis[next_x][next_y]) {
                vis[next_x][next_y] = 1;
                que[rear].x = next_x;
                que[rear].y = next_y;
                que[rear].step = cnt.step + 1;
                que[rear].father = front;
                memcpy(que[rear].pre, s_name[i], sizeof(s_name[i]));
                rear++;
            }
        }
        front++;
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    memset(que, 0, sizeof(que));
    char temp[20];
    scanf("%s", temp);
    s_x = temp[0] - 'a' + 1;
    s_y = temp[1] - '0';
    scanf("%s", temp);
    d_x = temp[0] - 'a' + 1;
    d_y = temp[1] - '0';
//    printf("%d %d:%d %d", s_x, s_y, d_x, d_y);
    int ans = bfs();
    printf("%d\n", que[ans].step);
    printAns(ans);
    return 0;
}
