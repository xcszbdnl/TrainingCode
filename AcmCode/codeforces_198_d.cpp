#include <cstdio>
#include <cstring>

const int MAX_NUMBER = 1007;

int tree_array[2][2][MAX_NUMBER][MAX_NUMBER];
int n, m;
int lowbit(int x) {
    return x & (-x);
}
void add(int x, int y, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= n; j += lowbit(j)) {
            tree_array[x & 1][y & 1][i][j] ^= v;
        }
    }
//    for (int x_1 = x; x <= n; x += lowbit(x)) {
//        for (int y_1 = y ; y <= n; y += lowbit(y)) {
////            printf("x:y[%d][%d]\n", x, x);
//            tree_array[x_1 & 1][y_1 & 1][x][y] ^= v;
//        }
//    }
}

int getsum(int x, int y) {
    int ret = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        for (int j = y; j > 0; j -= lowbit(j)) {
            ret ^= tree_array[x & 1][y & 1][i][j];
        }
    }
    return ret;
}
int main() {
//    freopen("input.txt", "r", stdin);
    memset(tree_array, 0, sizeof(tree_array));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int x_1, y_1, x_2, y_2, val, type;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d%d%d%d", &x_1, &y_1, &x_2, &y_2);
            int ans = getsum(x_2, y_2);
            ans ^= getsum(x_1 - 1, y_1 - 1);
            ans ^= getsum(x_1 - 1, y_2);
            ans ^= getsum(x_2, y_1 - 1);
            printf("%d\n", ans);
        }
        else {
            scanf("%d%d%d%d%d", &x_1, &y_1, &x_2, &y_2, &val);
            add(x_1, y_1, val);
            add(x_1, y_2 + 1, val);
            add(x_2 + 1, y_1, val);
            add(x_2 + 1, y_2 + 1, val);
        }
    }
    return 0;
}
