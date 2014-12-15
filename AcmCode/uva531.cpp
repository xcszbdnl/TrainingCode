#include <cstdio>
#include <string.h>


#define MAX_WORD 101
#define WORD_LENGTH 32


int dp[MAX_WORD][MAX_WORD];
int path[MAX_WORD][MAX_WORD];
char text_1[MAX_WORD][WORD_LENGTH];
char text_2[MAX_WORD][WORD_LENGTH];
int length_1, length_2, flag;

void solve() {
    for (int i = 1; i <= length_1; i++) {
        for (int j = 1; j <= length_2; j++) {
            if (strcmp(text_1[i], text_2[j]) == 0) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                path[i][j] = 1;
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                path[i][j] = 2;
            }
            else {
                dp[i][j] = dp[i][j - 1];
                path[i][j] = 3;
            }
        }
    }
}

void printPath(int i, int j) {
    if (i == 0 || j == 0) {
        return ;
    }
    if (path[i][j] == 1) {
        printPath(i - 1, j - 1);
        if (flag) {
            printf("%s", text_1[i]);
            flag = 0;
        }
        else {
            printf(" %s", text_1[i]);
        }
    }
    else if (path[i][j] == 2) {
        printPath(i - 1, j);
    }
    else {
        printPath(i, j - 1);
    }
}

int main() {

    while (1) {
        memset(dp, 0, sizeof(dp));
        length_1 = 1;
        if (scanf("%s", text_1[length_1]) == EOF) {
            break;
        }
        length_1++;
        while (scanf("%s", text_1[length_1]) != EOF) {
            if (text_1[length_1][0] == '#') {
                break;
            }
            length_1++;
        }
        length_2 = 1;
        while (scanf("%s", text_2[length_2]) != EOF) {
            if (text_2[length_2][0] == '#') {
                break;
            }
            length_2++;
        }
        solve();
        length_1--;
        length_2--;
        flag = 1;
        printPath(length_1, length_2);
        printf("\n");
    }
    return 0;
}
