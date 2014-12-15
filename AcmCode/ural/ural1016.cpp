#include <cstdio>
#include <cstring>
#include <vector>

const int INF = 100000007;
int cube[70][10];
int step[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
int dist[70];
int start, end, father[70];
int que[10007];

void spfa() {
    for (int i = 0; i < 64; i++) {
        dist[i] = INF;
    }
    dist[start] = cube[start][4];
    int font = 0;
    int rear = 1;
    que[front] = start;
    while (front < rear) {
        int cnt = que[front];
        int row = cnt / 8;
        int col = cnt % 8;
        int next_r, next_c;
        for (int i = 0; i < 4; i++) {
            next_r = row + step[i][0];
            next_c = col + step[i][1];
            int next = next_r * 8 + next_c;
            if (next > 0 && next < 64) {
                if (i == 0 && dist[next] > dist[cnt] + cube[start][1]) {
                    dist[next] = dist[cnt] + cube[start][1];
                    memcpy(cube[next], cube[cnt], sizeof(cube[cnt]));
                    int temp = cube[next][4];
                    cube[next][4] = cube[next][1];
                    cube[next][1] = cube[next][4];
                }
            }
        }
    }
}
int main() {
    freopen("input.txt", "r", stdin);;
    char temp[20];
    scanf("%s", temp);
    start = temp[0] - 'a' + (temp[1] - '0') * 8;
    scanf("%s", temp);
    end = temp[0] - 'a' + (temp[1] - '0') * 8;
    for (int i = 0; i < 6; i++) {
        scanf("%d", &cube[start][i]);
    }
    spfa();
    printAns();
}
