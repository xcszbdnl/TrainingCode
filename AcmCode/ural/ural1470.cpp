#include <cstdio>
#include <cstring>

const int maxn = 140;

long long tree[maxn][maxn][maxn];

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int y, int z, int val) {
    for (int i = x; i < maxn; i += lowbit(i)) {
        for (int j = y; j < maxn; j += lowbit(j)) {
            for (int k = z; k < maxn; k += lowbit(k)) {
                tree[i][j][k] += val;
            }
        }
    }
}

long long sum(int x, int y, int z) {
    long long ret = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        for (int j = y; j > 0; j -= lowbit(j)) {
            for (int k = z; k > 0; k -= lowbit(k)) {
                ret += tree[i][j][k];
            }
        }
    }
    return ret;
}

int n;

int main() {
//    freopen("in.txt", "r", stdin);
    memset(tree, 0, sizeof(tree));
    scanf("%d", &n);
    int m;
    memset(tree, 0, sizeof(tree));
    while (scanf("%d", &m) != EOF) {
        if (m == 3) {
            break;
        }
        else if (m == 1) {
            int x, y, z, k;
            scanf("%d%d%d%d", &x, &y, &z, &k);
            x++, y++, z++;
            add(x, y, z, k);
        }
        else {
            int x1, y1, z1, x2, y2, z2;
            scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
            x2++, y2++, z2++;
            x1++, y1++, z1++;
            printf("%I64d\n", sum(x2, y2, z2)-sum(x2, y1-1, z2)-sum(x1-1, y2, z2)+sum(x1-1, y1-1, z2)-(sum(x2, y2, z1-1)-sum(x2, y1-1, z1-1)-sum(x1-1, y2, z1-1)+sum(x1-1, y1-1, z1-1)));
        }
    }
    return 0;
}
