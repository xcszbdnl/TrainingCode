#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <map>

using namespace std;
const int maxn = 1000007;
map<int, long long> ans, cnt, pre;
int val[maxn], n;
map<int, long long>::iterator it;
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    for (int i = 1; i <= n; i++) {
        cnt.clear();
        for (it = pre.begin(); it != pre.end(); it++) {
            int cnt_gcd = it->first;
            int cnt_num = it->second;
            cnt_gcd = gcd(cnt_gcd, val[i]);
            cnt[cnt_gcd] += cnt_num;
//            printf("%d-->cnt[%d]:%d\n", i, cnt_gcd, cnt[cnt_gcd]);
        }
        cnt[val[i]] += 1;
        swap(cnt, pre);
        for (it = pre.begin(); it != pre.end(); it++) {
            ans[it->first] += it->second;
        }
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int x;
        scanf("%d", &x);
        printf("%I64d\n", ans[x]);
    }
    return 0;
}
