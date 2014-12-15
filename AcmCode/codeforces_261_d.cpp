#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
using namespace std;
const int maxn = 1000007;

map<long long, long long> maps;
long long val[maxn];
long long pre[maxn], last[maxn];
long long tree[maxn];
int n;


int lowbit(int x) {
    return x & (-x);
}

void add(int x, int val) {
    while (x < maxn) {
        tree[x] += val;
        x += lowbit(x);
    }
}

long long sum(int x) {
    long long ret = 0;
    while (x > 0) {
        ret += tree[x];
        x -= lowbit(x);
    }
    return ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    memset(pre, 0, sizeof(pre));
    memset(last, 0, sizeof(last));
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    maps.clear();
    for (int i = 1; i <= n; i++) {
        if (maps.count(val[i])) {
            maps[val[i]]++;
        }
        else {
            maps[val[i]] = 1;
        }
        pre[i] = maps[val[i]];
    }
    maps.clear();
    for (int i = n; i >= 1; i--) {
        if (maps.count(val[i])) {
            maps[val[i]]++;
        }
        else {
            maps[val[i]] = 1;
        }
        last[i] = maps[val[i]];
        add(last[i], 1);
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        add(last[i], - 1);
        long long cnt = sum(pre[i] - 1);
        ans += cnt;
    }
    cout << ans << endl;
    return 0;
}
