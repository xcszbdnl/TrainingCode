#include <cstdio>
#include <cstring>

const int maxn = 50007;

int father[maxn], r[maxn];

int find(int a) {
    if (a == father[a]) {
        return a;
    }
    else {
        int t = father[a];
        father[a] = find(father[a]);
        r[a] = (r[a] + r[t]) % 3;
        return father[a];
    }
}

void union_set(int a, int b, int d) {
    int x = find(a);
    int y = find(b);
    father[y] = x;
    r[y] = (r[a] + d - 1 + 3 - r[b]) % 3;
}

int main() {
//    freopen("input.txt", "r", stdin);
    int n, m;
    int ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        r[i] = 0;
    }
    while (m--) {
        int type, a, b;
        scanf("%d%d%d", &type, &a, &b);
        if (a > n || b > n || (type == 2 && a == b)) {
            ans++;
            continue;
        }
        int x = find(a);
        int y = find(b);
        if (x == y) {
            if ((type == 1 && (r[a] != r[b]))) {
                ans++;
            }
            else if (type == 2 && (3 - r[a] + r[b]) % 3 != 1) {
                ans++;
            }
        }
        else {
            union_set(a, b, type);
        }
    }
    printf("%d\n", ans);
    return 0;
}
