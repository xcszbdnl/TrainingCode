#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100007;
const int INF = 1000 * 1000 * 1000;
int fa[maxn], val[maxn], max_wage[maxn], mx[maxn];
int ans[maxn];
int n, m, flag;

int findFa(int x) {
    if (x == fa[x]) {
        return x;
    }
    int cnt_fa = fa[x];
    fa[x] = findFa(fa[x]);
    val[x] += val[cnt_fa];
    return fa[x];
}

int unionSet(int a, int b, int c) {
    int x = findFa(a);
    int y = findFa(b);
    if (x == y) {
        return 1;
    }
    if (b == 0) {
        ans[x] = c + val[a];
        ans[y] = val[b];
        ans[a] = c;
    }
    if (val[a] + c > val[b]) {
        fa[y] = x;
        int temp = val[a] + c - val[b];
        mx[x] = max(mx[x], mx[y] + temp);
        if (mx[x] > INF) {
            flag = 1;
        }
        val[y] = temp;
        if (ans[y] != -1) {
            ans[x] = ans[y] + val[y];
        }
        if (ans[x] != -1) {
            if (mx[x] > ans[x]) {
                flag = 1;
            }
        }
    }
    else {
        fa[x] = y;
        int temp = val[b] - c - val[a];
        mx[y] = max(mx[y], mx[x] + temp);
        if (mx[y] > INF) {
            flag = 1;
        }
        val[x] = temp;
        if (ans[x] != -1) {
            ans[y] = ans[x] + val[x];
        }
        if (ans[y] != -1) {
            if (mx[y] > ans[y]) {
                flag = 1;
            }
        }
    }
    return 0;
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    int i;
    flag = 0;
    memset(val, 0, sizeof(val));
    memset(ans, -1, sizeof(ans));
    memset(mx, 0, sizeof(mx));
    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }
    ans[0] = 0;
    for (i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (c < 0) {
            c = -c;
            swap(a, b);
        }
        if (a == 0 && c > 0) {
            flag = 1;
            break;
        }
        if (unionSet(a, b, c) && val[a] + c != val[b]) {
            flag = 1;
            break;
        }
        if (flag) {
            break;
        }
    }
    if (flag) {
        printf("Impossible after %d statements\n", i);
        return 0;
    }
    for (int i = 0; i < n; i++) {
        findFa(i);
    }
    int f0 = findFa(0);
    ans[0] = 0;
    ans[f0] = val[0];
    for (int i = 1; i < n; i++) {
        int cnt_fa = findFa(i);
        if (cnt_fa != f0 && cnt_fa == i) {
            ans[i] = INF;
        }
        if (cnt_fa == f0 && cnt_fa != i) {
            ans[i] = ans[f0] - val[i];
        }
    }
    for (int i = 1; i < n; i++) {
        int cnt_fa = findFa(i);
        if (ans[cnt_fa] == INF) {
            ans[i] = ans[cnt_fa] - val[i];
        }
    }
    printf("Possible\n");
    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
