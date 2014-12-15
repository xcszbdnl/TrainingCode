#include <cstdio>
#include <cstring>

const int maxn = 30007;
int father[maxn], num[maxn];

int find(int x) {
    if (x == father[x]) {
        return x;
    }
    father[x] = find(father[x]);
    return father[x];
}

int main() {
//    freopen("input.txt", "r", stdin);
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (!n && !m) {
            break;
        }
        for (int i = 0; i < n; i++) {
            father[i] = i;
            num[i] = 1;
        }
        for (int i = 1; i <= m; i++) {
            int k;
            scanf("%d", &k);
            int first = 1;
            int y;
            for (int j = 1; j <= k; j++) {
                int cnt;
                scanf("%d", &cnt);
                if (first) {
                    first = 0;
                    y = find(cnt);
                }
                else {
                    cnt = find(cnt);
                    if (cnt != y) {
                        father[cnt] = y;
                        num[y] += num[cnt];
                    }
                }
            }
        }
        int y = find(0);
        printf("%d\n", num[y]);
    }
    return 0;
}
