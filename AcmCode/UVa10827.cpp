#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;
const int MAX_NUMBER = 80;
const int  MAX_SUM = -1000001;
int arrays[MAX_NUMBER][MAX_NUMBER];
int sums[MAX_NUMBER][MAX_NUMBER];
int n;
void pre_solve() {
    for (int i = 1; i <= n; i++) {
        sums[i][0] = 0;
        sums[0][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + arrays[i][j];
        }
    }
}
int solve() {
    int max_number = MAX_SUM;
    for (int row_1 = 1; row_1 <= n; row_1++) {
        for (int row_2 = row_1; row_2 <= n; row_2++) {
            int  final_max;
            int n_start_min = sums[row_2][n] - sums[row_2][n - 1] - sums[row_1- 1][n] + sums[row_1 - 1][n - 1];
            int n_all_min = sums[row_2][n] - sums[row_2][n - 1] - sums[row_1 - 1][n] + sums[row_1 - 1][n - 1];
            int n_start_max = sums[row_2][n] - sums[row_2][n - 1] - sums[row_1 - 1][n] + sums[row_1 - 1][n - 1];
            int n_all_max = sums[row_2][n] - sums[row_2][n - 1] - sums[row_1 - 1][n] + sums[row_1 - 1][n - 1];
            for (int i = n - 1; i >= 1; i--) {
                
                if (n_start_max < 0) {
                    n_start_max = 0;
                }
                n_start_max += sums[row_2][i] - sums[row_2][i - 1] - sums[row_1 - 1][i] + sums[row_1 - 1][i - 1];
                if (n_start_max > n_all_max) {
                    n_all_max = n_start_max;
                }
                
                if (n_start_min > 0) {
                    n_start_min = 0;
                }
                n_start_min += sums[row_2][i] - sums[row_2][i - 1] - sums[row_1 - 1][i] + sums[row_1 - 1][i - 1];
                if (n_start_min < n_all_min) {
                    n_all_min = n_start_min;
                }
                
                int torus = sums[row_2][n] - sums[row_1 - 1][n] - n_all_min;
                
                if (torus < n_all_max) {
                    final_max = n_all_max;
                }
                
                else {
                    final_max = torus;
                }
                
                if (final_max > max_number) {
                    max_number = final_max;
                }
            }
        }
    }
    for (int column_1 = 1; column_1 <= n; column_1++) {
        for (int column_2 = column_1; column_2 <= n; column_2++) {
            int final_max;
            int n_start_max = sums[n][column_2] - sums[n - 1][column_2] - sums[n][column_1 - 1] + sums[n - 1][column_1 - 1];
            int n_all_max = sums[n][column_2] - sums[n - 1][column_2] - sums[n][column_1 - 1] + sums[n - 1][column_1 - 1];
            int n_start_min = sums[n][column_2] - sums[n - 1][column_2] - sums[n][column_1 - 1] + sums[n - 1][column_1 - 1];
            int n_all_min = sums[n][column_2] - sums[n - 1][column_2] - sums[n][column_1 - 1] + sums[n - 1][column_1 - 1];
            for (int i = n - 1; i >= 1; i--) {
                if (n_start_max < 0) {
                    n_start_max = 0;
                }
                n_start_max += sums[i][column_2] - sums[i - 1][column_2] - sums[i][column_1 - 1] + sums[i - 1][column_1 - 1];
                if (n_start_max > n_all_max) {
                    n_all_max = n_start_max;
                }

                if (n_start_min > 0) {
                    n_start_min = 0;
                }
                n_start_min += sums[i][column_2] - sums[i - 1][column_2] - sums[i][column_1 - 1] + sums[i - 1][column_1 - 1];
                if (n_start_min < n_all_min) {
                    n_all_min = n_start_min;
                }
                int torus = sums[n][column_2] - sums[n][column_1 - 1] - n_all_min;
                if (torus < n_all_max) {
                    final_max = n_all_max;
                }
                else {
                    final_max = torus;
                }

                if (final_max > max_number) {
                    max_number = final_max;
                }
            }
        }
    }
    return max_number;
}
        
int main() {
    freopen("input.txt","r",stdin);
    int test_case;
    cin >> test_case;
    while (test_case--) {
        memset(arrays,0,sizeof(arrays));
        memset(sums,0,sizeof(sums));
        cin >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> arrays[i][j];
            }
        }
       pre_solve();
       int max =  solve();
       cout << max << endl;
    }
    return 0;
}
