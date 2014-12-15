#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <map>

const int maxn = 100007;
using namespace std;
int n, a, b;
int val[maxn], vis[maxn], fa[maxn], sta[maxn];
map<int, int> maps;

int findFa(int x) {
    if (x == fa[x]) {
        return x;
    }
    return fa[x] = findFa(fa[x]);
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &n, &a, &b);
    memset(vis, 0, sizeof(vis));
    maps.clear();
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
        fa[i] = i;
        maps[val[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        int c = a - val[i];
        if (maps.count(c)) {
            int x = findFa(maps[c]);
            int y = findFa(i);
            fa[y] = x;
            vis[i] |= 1;
        }
        int d = b - val[i];
        if (maps.count(d)) {
            int x = findFa(maps[d]);
            int y = findFa(i);
            fa[y] = x;
            vis[i] |= 2;
        }
    }
    for (int i = 1; i <= n; i++) {
        sta[i] = 3;
    }
    for (int i = 1; i <= n; i++) {
        int x = findFa(i);
        sta[x] = sta[x] & vis[i];
    }
    for (int i = 1; i <= n; i++) {
        if (sta[i] == 0) {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    for (int i = 1; i <= n; i++) {
        int x = findFa(i);
        printf("%d ", sta[x] & 1 ? 0 : 1);
    }
    printf("\n");
    return 0;
}
