#include <cstdio>
#include <cstring>

const int maxn = 110;
int maps[maxn][maxn];

int main() {
//    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    memset(maps, 0, sizeof(maps));
    for (int i = 1; i <= n / 2; i++) {
        int num = (i - 1) * 2 + 1;
        maps[i][n / 2 + 1] = 1;
        int loc = n / 2 + 1;
        num--;
        for (int j = 1; num > 0; j++) {
            maps[i][loc + j] = 1;
            maps[i][loc - j] = 1;
            num -= 2;
        }
    }
    for (int i = n; i >= n / 2 + 1; i--) {
        int num = (n - i) * 2 + 1;
        int loc = n / 2 + 1;
        maps[i][n / 2 + 1] = 1;
        num--;
        for (int j = 1; num > 0; j++) {
            maps[i][loc + j] = 1;
            maps[i][loc - j] = 1;
            num -= 2;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (maps[i][j] == 1) {
                printf("D");
            }
            else {
                printf("*");
            }
        }
        printf("\n");
    }
    return 0;
}
