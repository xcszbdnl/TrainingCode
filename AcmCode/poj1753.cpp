#include <cstdio>
#include <cstring>


const int maxn = 65539;
struct State {
    int round[17];
    int step;
};
struct State state[maxn];
int vis[maxn], steps[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int getHash(struct State cnt) {
    int cnt_number = 0;
    for (int i = 0; i < 16; i++) {
        cnt_number = cnt_number * 2 + cnt.round[i];
    }
    return cnt_number;
}

int bfs() {
    int front = 0;
    int rear = 1;
    memset(vis, 0, sizeof(vis));
    int cnt_hash = getHash(state[0]);
    vis[cnt_hash] = 1;
    state[0].step = 0;
    while (front < rear) {
        struct State cnt = state[front];
        cnt_hash = getHash(cnt);
//        printf("%d\n", cnt_hash);
        if (cnt_hash == 0 || cnt_hash == ((1 << 16) - 1 )) {
            return cnt.step;
        }
        for (int i = 0; i < 16; i++) {
            int temp[17];
            memcpy(temp, cnt.round, sizeof(cnt.round));
            int cnt_x = i / 4;
            int cnt_y = i % 4;
            temp[i] = 1 - temp[i];
            for (int j = 0; j < 4; j++) {
                int next_x = cnt_x + steps[j][0];
                int next_y = cnt_y + steps[j][1];
                if (next_x >= 0 && next_x < 4 && next_y >= 0 && next_y < 4) {
                    temp[next_x * 4 + next_y] = 1 - temp[next_x * 4 + next_y];
                }
            }
            memcpy(state[rear].round, temp, sizeof(temp));
            cnt_hash = getHash(state[rear]);
            if (!vis[cnt_hash]) {
                vis[cnt_hash] = 1;
                state[rear].step = cnt.step + 1;
                rear++;
            }
        }
        front++;
    }
    return -1;
}

int main() {
//    freopen("input.txt", "r", stdin);
    memset(state, 0, sizeof(state));
    char temp[10];
    for (int i = 0; i < 4; i++) {
        scanf("%s", temp);
        for (int j = 0; j < 4; j++) {
            if (temp[j] == 'b') {
                state[0].round[i * 4 + j] = 0;
            }
            else {
                state[0].round[i * 4 + j] = 1;
            }
        }
    }
    int min_number = bfs();
    if (min_number >= 0) {
        printf("%d\n", min_number);
    }
    else {
        printf("Impossible\n");
    }
    return 0;
}
