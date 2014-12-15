/**
 *FILENAME：poj1753.c
 *AUHTOR: XIANG CHANG SHENG
 *CREATE ON: 2013-2-14
 */

#include <stdio.h>
#include <string.h>

#define MAX_NUMBER  100000

struct Rectangular {
    int state[16];
    int distance;
};
struct Rectangular rectangular[MAX_NUMBER];
int vis[MAX_NUMBER];
int ans_1[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int ans_2[16] = {0};
int ans = 0;
int flag;
void turn_pieces(int order, int front, int rear) {
    int row = order / 4;
    int column = order % 4;
    int location;
    if (row > 0) {
        location = (row - 1) * 4 + column;
        rectangular[rear].state[location] = !rectangular[front].state[location];
    }
    if (row < 3) {
        location = (row + 1) * 4 + column;
        rectangular[rear].state[location] = !rectangular[front].state[location];
    }
    if (column > 0) {
        location = row * 4 + column - 1;
        rectangular[rear].state[location] = !rectangular[front].state[location];
    }
    if (column < 3) {
        location = row * 4 + column + 1;
        rectangular[rear].state[location] = !rectangular[front].state[location];
    }
    rectangular[rear].state[order] = !rectangular[front].state[order];
}

int turn_to_hash(int front) {
    int number = 0;
    int i;
    for (i = 0; i < 16; i++) {
        number = number << 1 + rectangular[front].state[i];
    }
    return number;
}

void bfs() {
    int front = 0, rear = 1;
    int i, row, column;
    int visited, hash;
    while (front < rear) {
        hash = turn_to_hash(front);
        if (hash == 65535 || hash == 0) {
            ans = rectangular[front].distance;
            break;
        }
        else {
            for (i = 0; i < 16; i++) {
                turn_pieces(i, front, rear);
                visited = turn_to_hash(rear);
                if (!vis[visited]) {
                    vis[visited] = 1;
                    rectangular[rear].distance = rectangular[front].distance + 1;
                    rear++;
                }
            }
        }
        front++;
    }
    flag = 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    int i, j;
    char input[4];
    for(i = 0; i < 4; i++) {
        scanf("%s", input);
        for (j = 0; j < 4; j++) {
            if (input[j] == 'w') {
                rectangular[0].state[i * 4 + j] = 0;
            }
            else {
                rectangular[0].state[i * 4 + j] = 1;
            }
        }
    }
    memset(vis, 0, sizeof(vis));
    flag = 0;
    bfs();
    if (flag) {
        printf("Impossible\n");
    }
    else {
        printf("%d\n", ans);
    }
    return 0;
}
