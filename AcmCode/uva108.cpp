#include <iostream>
#include <stdio.h>
using namespace std;
const int MAX_NUMBER = 150;
const int MINIMUM = -100000;
int arrays[MAX_NUMBER][MAX_NUMBER];
int sum[MAX_NUMBER][MAX_NUMBER];
int n;
void pre_solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j<= n; j++) {
            sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + arrays[i][j];
        }
    }
}
int solve() {
    int max_sum = MINIMUM;
    int n_start, n_all;
    for (int row_1 = 0; row_1 <= n; row_1++) {
        for (int row_2 = row_1 + 1; row_2 <= n; row_2++) {
            n_start = sum[row_2][n] - sum[row_1 - 1][n] - sum[row_2][n - 1] + sum[row_1 - 1][n - 1];
            n_all = sum[row_2][n] - sum[row_1 - 1][n] - sum[row_2][n - 1] + sum[row_1 - 1][n - 1];
            for (int i = n - 1; i >= 1; i--) {
                if (n_start < 0) {
                    n_start = 0;
                }
                n_start += sum[row_2][i] - sum[row_1 - 1][i] - sum[row_2][i - 1] + sum[row_1 - 1][i - 1];
                if (n_start > n_all) {
                    n_all = n_start;
                }
                if (n_all > max_sum) {
                    max_sum = n_all;
                }
            }
        }
    }
    return max_sum;
}
int main() {
    freopen("input.txt","r",stdin);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arrays[i][j];
        }
    }
    for (int i = 0; i <= n ; i++) {
        sum[i][0] = 0;
        sum[0][i] = 0;
    }
    int max_sum;
    pre_solve();
    max_sum = solve();
    cout << max_sum << endl;
    return 0;
}

    
