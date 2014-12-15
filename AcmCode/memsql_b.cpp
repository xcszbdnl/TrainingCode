#include <cstdio>
#include <cstring>
#include <cmath>
int n, m;

double getDist(int x1, int y1, int x2, int y2) {
    int x = x1 - x2;
    int y = y1 - y2;
    x = x * x;
    y = y * y;
    return sqrt((x + y) * 1.0);
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    if (n == 0) {
        printf("0 1\n");
        printf("0 %d\n", m);
        printf("0 0\n");
        printf("0 %d\n", m - 1);
    }
    else if (m == 0) {
        printf("1 0\n");
        printf("%d 0\n", n);
        printf("0 0\n");
        printf("%d 0\n", n - 1);
    }
    else {
        printf("0 0\n");
        printf("%d %d\n", n, m);
        double max_len = 0;
        int ans_1, ans_2;
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j <= n - 1; j++) {
                double len = getDist(n, m, n, j) + getDist(n, j, 0, i);
                if (len > max_len) {
                    ans_1 = i;
                    ans_2 = j;
                    max_len = len;
                }
            }
        }
        printf("%d %d\n", n, ans_2);
        printf("0 %d\n", ans_1);
    }
    return 0;
}
