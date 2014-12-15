#include <cstdio>
#include <string.h>



long long value[400][400];
int vis[400][400];
int n, d;

void search(int length, int depth) {
    if (vis[length][depth]) {
        return ;
    }
    vis[length][depth] = 1;
    value[length][depth] = 0;
    if (length > 2) {
        search(length - 2, depth - 1);
        value[length][depth] += value[length - 2][depth - 1];
        for (int i = 2; i < length; i += 2) {
            search(i, depth);
            for (int k = 0; k <= depth; k++) {
                search(length - i, k);
                value[length][depth] += 2 * value[i][depth] * value[length - i][k];
            }
        }
        if (length % 4 == 0) {
            value[length][depth] -= value[length / 2][depth];
        }

    }
    return ;
}

int main() {
    freopen("input.txt", "r", stdin);
    memset(value, 0, sizeof(value));
    value[2][1] = 1;
    vis[2][1] = 1;
    while (scanf("%d%d", &n, &d) != EOF) {
        search(n, d);
        printf("%lld\n", value[n][d]);
    }
}
