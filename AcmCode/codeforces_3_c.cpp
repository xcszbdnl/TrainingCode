#include <cstdio>
#include <cstring>

const int maxn = 10;

char input[maxn][maxn];
int n_x, n_o, n_dot;


bool judge(int x, int y, char c) {
    int number = 0;
    for (int i = 1; i <= 3; i++) {
        if (input[x][i] == c) {
            number++;
        }
    }
    if (number == 3) {
        return 1;
    }
    number = 0;
    for (int i = 1; i <= 3; i++) {
        if (input[i][y] == c) {
            number++;
        }
    }
    if (number == 3) {
        return 1;
    }
    if (x == y) {
        if (input[1][1] == c && input[2][2] == c && input[3][3] == c) {
            return 1;
        }
    }
    if ((x == 1 && y == 3) || (x == 2 && y == 2) || (x == 3 && y == 1)) {
        if (input[2][2] == c && input[1][3] == c && input[3][1] == c) {
            return 1;
        }
    }
    return 0;
}
int main() {
//    freopen("input.txt", "r", stdin);
    int win_flag, winner, il;
    win_flag = winner = 0;
    n_x = n_o = n_dot = 0;
    il = 0;
    memset(input, 0, sizeof(input));
    for (int i = 1; i <= 3; i++) {
        scanf("%s", input[i] + 1);
//        printf("%s\n", input[i] + 1);
    }
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (input[i][j] == '.') {
                n_dot++;
            }
            else if (input[i][j] == 'X') {
                n_x++;
            }
            else {
                n_o++;
            }
        }
    }
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (input[i][j] == 'X') {
                if (judge(i, j, 'X')) {
                    if (win_flag && winner != 1) {
                        il = 1;
                    }
                    win_flag = 1;
                    winner = 1;
                }
            }
            else if (input[i][j] == '0') {
                if (judge(i, j, '0')) {
                    if (win_flag && winner != 0) {
                        il = 1;
                    }
                    win_flag = 1;
                    winner = 0;
                }
            }
        }
    }
    if ((n_x != n_o && (n_x != n_o + 1)) || il ) {
        printf("illegal\n");
    }
    else if (win_flag) {
        if (winner && (n_x == n_o + 1)) {
            printf("the first player won\n");
        }
        else if (!winner && (n_x == n_o)){
            printf("the second player won\n");
        }
        else {
            printf("illegal\n");
        }
    }
    else {
        if (n_dot == 0) {
            printf("draw\n");
        }
        else if (n_x == n_o + 1) {
            printf("second");
        }
        else if (n_x == n_o) {
            printf("first\n");
        }
    }
}
