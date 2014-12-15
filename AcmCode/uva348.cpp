#include <string.h>
#include <cstdio>

#define MAX_NUMBER 20
#define INF 2000000000

long long dp[MAX_NUMBER][MAX_NUMBER];
int path[MAX_NUMBER][MAX_NUMBER];
int row_column[MAX_NUMBER];
int matrix_number;

void solve() {
    for (int length = 2; length <= matrix_number; length++) {
        for (int i = 1; i <= matrix_number - length + 1; i++) {
            int j = i + length - 1;
            dp[i][j] = INF;
            for (int k = i; k <= j - 1; k++) {
                long long min_ans = dp[i][k] + dp[k + 1][j] + row_column[i - 1] * row_column[k] * row_column[j];
                if (min_ans < dp[i][j]) {
                    dp[i][j] = min_ans;
                    path[i][j] = k;
                }
            }
        }
    }
}

void printPath(int left, int right) {
    if (left == right) {
        printf("A%d", left);
    }
    else {
        printf("(");
        printPath(left, path[left][right]);
        printf(" x ");
        printPath(path[left][right] + 1, right);
        printf(")");
    }
}

int main() {

    int case_number = 1;
    while (scanf("%d", &matrix_number) != EOF) {
        if (matrix_number == 0) {
            break;
        }
        for (int i = 0; i < matrix_number; i++) {
            int row, column;
            scanf("%d%d", &row, &column);
            row_column[i] = row;
            row_column[i + 1] = column; 
        }
        memset(dp, 0, sizeof(dp));
        solve();
        printf("Case %d: ", case_number);
        printPath(1, matrix_number);
        printf("\n");
        case_number++;
    }
    return 0;
}
