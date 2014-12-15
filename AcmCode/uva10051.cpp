#include <string.h>
#include <cstdio>

const int MAX_CUBE = 3010;

int dp[MAX_CUBE];
int top[MAX_CUBE], bottom[MAX_CUBE], order[MAX_CUBE], next[MAX_CUBE];
char cube[6][10] = {"front", "back", "left", "right", "top", "bottom"};
int cube_number;


void search(int cnt_cube) {
    if (dp[cnt_cube] != -1) {
        return ;
    }
    dp[cnt_cube] = 1;
    for (int i = cnt_cube + 1; i < cube_number; i++) {
        if (order[i] > order[cnt_cube] && bottom[cnt_cube] == top[i]) {
            search(i);
            if (dp[i] + 1 > dp[cnt_cube]) {
                dp[cnt_cube] = dp[i] + 1;
                next[cnt_cube] = i;
            }
        }
    }
}

void printPath(int cnt_cube) {
    if (cnt_cube == -1) {
        return ;
    }
    printf("%d %s\n", order[cnt_cube] + 1, cube[cnt_cube % 6]);
    printPath(next[cnt_cube]);
}

int main() {

    int case_number = 1;
    int first = 1;
    while (scanf("%d", &cube_number) != EOF) {
        if (!cube_number) {
            break;
        }
        if (!first) {
            printf("\n");
        }
        for (int i = 0; i < cube_number; i++) {
            int front, back, left, right, up, down;
            scanf("%d%d%d%d%d%d", &front, &back, &left, &right, &up, &down);
            top[i * 6 + 0] = front, bottom[i * 6 + 0] = back, order[i * 6 + 0] = i;
            top[i * 6 + 1] = back, bottom[i * 6 + 1] = front, order[i * 6 + 1] = i;
            top[i * 6 + 2] = left, bottom[i * 6 + 2] = right, order[i * 6 + 2] = i;
            top[i * 6 + 3] = right, bottom[i * 6 + 3] = left, order[i * 6 + 3] = i;
            top[i * 6 + 4] = up, bottom[i * 6 + 4] = down, order[i * 6 + 4] = i;
            top[i * 6 + 5] = down, bottom[i * 6 + 5] = up, order[i * 6 + 5] = i;  
        }
        cube_number *= 6;
        memset(dp, -1, sizeof(dp));
        memset(next, -1, sizeof(next));
        for (int i = 0; i < cube_number; i++) {
            search(i);
        }
        int top_cube, max_ans = 0;
        for (int i = 0; i < cube_number; i++) {
            if (dp[i] > max_ans) {
                max_ans = dp[i];
                top_cube = i;
            }
        }
        printf("Case #%d\n", case_number);
        printf("%d\n", max_ans);
        printPath(top_cube);
        first = 0;
        case_number++;
    }
    return 0;
}
