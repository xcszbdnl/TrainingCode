/**
 *FILENAME: poj2965.c
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2013-2-25
 */

#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 150000

struct State {
    int cnt_state[4][4];
    int step;
    int process[2];
    int father;
};

struct State state[MAX_NUMBER];
int vis[MAX_NUMBER];
int ans = 1000000;
int last_step;

int hashCode(int order) {
    int hash_code = 0;
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            hash_code = hash_code * 2 + state[order].cnt_state[i][j];
        }
    }
    return hash_code;
}

void print_path(int father) {
    if (state[father].father != 0) {
        print_path(state[father].father);
    }
    printf("%d %d\n", state[father].process[0], state[father].process[1]);
}

void bfs() {
    int front, rear, hash_code;
    int i, j, row, column;
    front = 0, rear = 1;
    while (front < rear) {
        hash_code = hashCode(front);
        if (hash_code == 65535) {
            last_step = front;
            return ;
        }
        else {
            for (i = 0; i < 16; i++) {
                memcpy(state[rear].cnt_state, state[front].cnt_state, sizeof(state[front].cnt_state));                
                row = i / 4;
                column = i % 4;
                for (j = 0; j < 4; j++) {
                    state[rear].cnt_state[row][j] = !state[front].cnt_state[row][j];
                    state[rear].cnt_state[j][column] = !state[front].cnt_state[j][column];
                }
                hash_code = hashCode(rear);
                if (!vis[hash_code]) {
                    state[rear].father = front;
                    state[rear].process[0] = row + 1;
                    state[rear].process[1] = column + 1;
                    state[rear].step = state[front].step + 1;
                    vis[hash_code] = 1;
                    rear++;
                }
            }
        }
        front++;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    char input[5];
    int i, j;
    for (i = 0; i < 4; i++) {
        scanf("%s", input);
        for (j = 0; j < 4; j++) {
            if (input[j] == '+') {
                state[0].cnt_state[i][j] = 0;
            }
            else {
                state[0].cnt_state[i][j] = 1;
            }
        }
    }
    state[0].step = 0;
    memset(vis, 0, sizeof(vis));
    bfs();
    printf("%d\n", state[last_step].step);
    print_path(last_step);
}
