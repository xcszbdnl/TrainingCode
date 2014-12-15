#include <cstdio>
#include <cstring>


const int maxn = 65539;
struct State {
    int round;
    int step, father, loc;
};
struct State state[maxn];
int vis[maxn], ans;
//int getHash(struct State cnt) {
//    int cnt_number = 0;
//    for (int i = 0; i < 16; i++) {
//        cnt_number = cnt_number * 2 + cnt.round[i];
//    }
//    return cnt_number;
//}

int bfs() {
    int front = 0;
    int rear = 1;
    memset(vis, 0, sizeof(vis));
    vis[state[0].round] = 1;
    state[0].step = 0;
    state[0].father = -1;
    state[0].loc = 0;
    while (front < rear) {
        struct State cnt = state[front];
//        printf("%d\n", cnt.round);
        if (cnt.round == 0) {
            ans = front;
            return cnt.step;
        }
        for (int i = 0; i < 16; i++) {
            int temp = cnt.round;
            int cnt_x = i / 4;
            int cnt_y = i % 4;
            temp ^= (1 << i);
            for (int j = 0; j < 4; j++) {
                int next_loc = cnt_x * 4 + j;
                temp ^= (1 << next_loc);
                next_loc = j * 4 + cnt_y;
                temp ^= (1 << next_loc);
            }
            if (!vis[temp]) {
                vis[temp] = 1;
                state[rear].round = temp;
                state[rear].father = front;
                state[rear].loc = i;
                state[rear].step = cnt.step + 1;
                rear++;
            }
        }
        front++;
    }
    return -1;
}

void printAns(int cnt) {
//    printf("test\n");
    if (state[cnt].father != -1) {
        printAns(state[cnt].father);
        printf("%d %d\n", state[cnt].loc / 4 + 1, state[cnt].loc % 4 + 1);
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    memset(state, 0, sizeof(state));
    char temp[10];
    for (int i = 0; i < 4; i++) {
        scanf("%s", temp);
        for (int j = 0; j < 4; j++) {
            if (temp[j] == '+') {
                int loc = i * 4 + j;
                state[0].round += (1 << loc);
            }
        }
    }
//    printf("%d\n", state[0].round);
    int min_number = bfs();
    printf("%d\n", min_number);
    printAns(ans);
    return 0;
}
