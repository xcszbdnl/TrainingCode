#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 50;

int matrix[maxn][maxn];
int temp[maxn][maxn];
int maps[maxn][maxn];
int step[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};


void solve() {
    int i = 0, j = 0;
    while (i < 30 && j < 30) {
        int r = i;
        for (int k = i; k < 30; k++) {
            if (matrix[k][j]) {
                r = k;
                break;
            }
        }
        if (r != i) {
            for (int k = j; k <= 30; k++) {
                swap(matrix[i][k], matrix[r][k]);
            }
        }
        if (matrix[i][j]) {
            for (int k = i + 1; k < 30; k++) {
                if (matrix[k][j]) {
                    for (int s = j; s <= 30; s++) {
                        matrix[k][s] ^= matrix[i][s];
                    }
                }
            }
            i++;
        }
        j++;
    }
    for (int i = 29; i >= 0; i--) {
        for (int j = i + 1; j < 30; j++) {
            matrix[i][30] ^= matrix[j][30] * matrix[i][j];
        }
        matrix[i][30] /= matrix[i][i];
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            int cnt_loc = i * 6 + j;
            matrix[cnt_loc][cnt_loc] = 1;
            for (int k = 0; k < 4; k++) {
                int next_x = i + step[k][0];
                int next_y = j + step[k][1];
                if (next_x >= 0 && next_x < 5 && next_y >= 0 && next_y < 6) {
                    int next_loc = next_x * 6 + next_y;
                    matrix[cnt_loc][next_loc] = 1;
                }
            }
        }
    }
    memcpy(temp, matrix, sizeof(matrix));
    int ncase = 1;
    while (test_case--) {
        memcpy(matrix, temp, sizeof(temp));
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                int x;
                scanf("%d", &x);
                int loc = i * 6 + j;
                matrix[loc][30] = x;
            }
        }
        solve();
        printf("PUZZLE #%d\n", ncase);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                int loc = i * 6 + j;
                printf("%d ", matrix[loc][30]);
            }
            printf("\n");
        }
        ncase++;
    }
    return 0;
}
