#include <cstdio>
#include <string.h>

#define MAX_NUMBER 150
#define max(a,b) ((a) > (b)) ? (a) : (b)

int dp[MAX_NUMBER][MAX_NUMBER];
char string_1[MAX_NUMBER], string_2[MAX_NUMBER];
int length_1, length_2;


void solve() {
    for (int i = 1; i <= length_1; i++) {
        for (int j = 1; j <= length_2; j++) {
            if (string_1[i - 1] == string_2[j - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            }
            else {
                dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
        }
    }
}

int main() {

    int case_number =  1;
    while (1) {
        gets(string_1);
        if (string_1[0] == '#') {
            break;
        }
        gets(string_2);
        length_1 = strlen(string_1);
        length_2 = strlen(string_2);
        memset(dp, 0, sizeof(dp));
        solve();
        printf("Case #%d: you can visit at most %d cities.\n", case_number, dp[length_1][length_2]);
        case_number++;
    }
    return 0;
}
