#include <cstdio>
#include <cstring>

#define min(a,b) ((a) > (b)) ? (b) : (a)
const int maxn = 1007;
int input[maxn][maxn];
int dp_1[maxn][maxn], fa_1[maxn][maxn], dp_2[maxn][maxn], fa_2[maxn][maxn], two[maxn][maxn], five[maxn][maxn];
int has_zero, z_x, z_y;
int n;

void printAns1(int x, int y) {
    if (fa_1[x][y] != -1) {
        if (fa_1[x][y] == 2) {
            printAns1(x - 1, y);
            printf("D");
        }
        else {
            printAns1(x, y - 1);
            printf("R");
        }
    }
}
void printAns2(int x, int y) {
    if (fa_2[x][y] != -1) {
        if (fa_2[x][y] == 1) {
            printAns2(x, y - 1);
            printf("R");
        }
        else {
            printAns2(x - 1, y);
            printf("D");
        }
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &input[i][j]);
        }
    }
    has_zero = 0;
    memset(two, 0, sizeof(two));
    memset(five, 0, sizeof(five));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (input[i][j] == 0) {
                has_zero = 1;
                z_x = i;
                z_y = j;
            }
            else {
                while (input[i][j] % 2 == 0) {
                    two[i][j]++;
                    input[i][j] /= 2;
                }
                while (input[i][j] % 5 == 0) {
                    five[i][j]++;
                    input[i][j] /= 5;
                }
            }

        }

    }
    memset(fa_1, -1, sizeof(fa_1));
    memset(fa_2, -1, sizeof(fa_2));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp_1[i][j] = 0;
            if (i == 1 && j == 1) {
                dp_1[1][1] = two[1][1];
                fa_1[1][1] = -1;
                dp_2[1][1] = five[1][1];
                fa_2[1][1] = -1;
                continue;
            }
            if (i == 1) {
                dp_1[i][j] = dp_1[i][j - 1] + two[i][j];
                fa_1[i][j] = 1;
                dp_2[i][j] = dp_2[i][j - 1] + five[i][j];
                fa_2[i][j] = 1;
                continue;
            }
            if (j == 1) {
                dp_1[i][j] = dp_1[i - 1][j] + two[i][j];
                fa_1[i][j] = 2;
                dp_2[i][j] = dp_2[i - 1][j] + five[i][j];
                fa_2[i][j] = 2;
                continue;
            }
            if (dp_1[i - 1][j] > dp_1[i][j - 1]) {
                dp_1[i][j] = dp_1[i][j - 1] + two[i][j];
                fa_1[i][j] = 1;
            }
            else {
                dp_1[i][j] = dp_1[i - 1][j] + two[i][j];
                fa_1[i][j] = 2;
            }
            dp_2[i][j] = 0;
            if (dp_2[i - 1][j] > dp_2[i][j - 1]) {
                dp_2[i][j] = dp_2[i][j - 1] + five[i][j];
                fa_2[i][j] = 1;
            }
            else {
                dp_2[i][j] = dp_2[i - 1][j] + five[i][j];
                fa_2[i][j] = 2;
            }
        }
//        for (int j = 1; j <= n; j++) {
//            printf("%d ", fa_2[i][j]);
//        }
//        printf("\n");
    }
    int ans = min(dp_1[n][n], dp_2[n][n]);
    if (has_zero && ans >= 2) {
        printf("1\n");
        for (int i = 1; i < z_x; i++) {
            printf("D");
        }
        for (int i = 1; i < n; i++) {
            printf("R");
        }
        for (int i = z_x; i < n; i++) {
            printf("D");
        }
        printf("\n");
    }
    else {
        printf("%d\n", ans);
        if (dp_1[n][n] < dp_2[n][n]) {
            printAns1(n, n);
        }
        else {
            printAns2(n, n);
        }
    }
    return 0;
}
