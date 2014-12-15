#include <cstdio>
#include <string.h>


const int MAX_STATE = 10;
const int MAX_LENGTH = 105;
const int MAX_METHOD = 70;

int dp[MAX_LENGTH][MAX_METHOD][MAX_METHOD];
int state[MAX_METHOD], maps[MAX_LENGTH], num[MAX_METHOD];
int state_number, row, column, max_state;

int check(int cnt_state) {
    for (int i = 0; i < max_state; i++) {
        if (cnt_state & (1 << i)) {
            if ((cnt_state & (1 << (i + 1))) || (cnt_state & (1 << (i + 2)))) {
                return 0;
            }
        }
    }
    return 1;
}

int getNum(int cnt_state) {
    int number = 0;
    for (int i = 0; i < max_state; i++) {
        if ((cnt_state & (1 << i))) {
            number++;
        }
    }
    return number;
}

int main() {

    scanf("%d%d", &row, &column);
    memset(dp, 0, sizeof(dp));
    memset(maps, 0, sizeof(maps));
    memset(state, 0, sizeof(state));
    state_number = 0;
    max_state = column;
    for (int i = 1; i <= row; i++) {
        char input[20];
        scanf("%s", input);
        for (int j = 0; input[j]; j++) {
            if (input[j] == 'H') {
                maps[i] = maps[i] | (1 << j);
            }
        }
    }
    for (int i = 0; i < (1 << max_state); i++) {
        if (check(i)) {
            state[state_number] = i;
            num[state_number] = getNum(i);
            state_number++;
        }
    }
    for (int i = 0; i < state_number; i++) {
        if (!(maps[1] & state[i])) {
            dp[1][i][0] = num[i];
        }
    }
    for (int i = 0; i < state_number; i++) {
        if (!(maps[2] & state[i])) {
            for (int j = 0; j < state_number; j++) {
                if (!(state[i] & state[j])) {
                    dp[2][i][j] = dp[1][j][0] + dp[2][i][j] + num[i];
                }
            }
        }
    }
    for (int i = 3; i <= row; i++) {
        for (int j = 0; j < state_number; j++) {
            if (!(maps[i] & state[j])) {
                for (int k = 0; k < state_number; k++) {
                    if (!(state[k] & state[j])) {
                        for (int m = 0; m < state_number; m++) {
                            if (!(state[m] & state[k]) && !(state[m] & state[j])) {
                                if (dp[i - 1][k][m] + num[j] > dp[i][j][k]) {
                                    dp[i][j][k] = dp[i - 1][k][m] + num[j];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < state_number; i++) {
        for (int j = 0; j < state_number; j++) {
            if (ans < dp[row][i][j]) {
                ans = dp[row][i][j];
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
