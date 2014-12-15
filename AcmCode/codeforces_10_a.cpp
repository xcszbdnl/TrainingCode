#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>


using namespace std;
int n, p1, p2, p3, t1, t2;
struct Seg {
    int l, r;
};
struct Seg seg[107];
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d%d%d%d%d", &n, &p1, &p2, &p3, &t1, &t2);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &seg[i].l, &seg[i].r);
    }
    int cnt_time = seg[1].l;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += (seg[i].r - seg[i].l) * p1;
        cnt_time = seg[i].r;
        if (i < n) {
            if (cnt_time + t1 < seg[i + 1].l) {
                ans += t1 * p1;
            }
            else {
                ans += (seg[i + 1].l - cnt_time) * p1;
                continue;
            }
            cnt_time += t1;
            if (cnt_time + t2 < seg[i + 1].l) {
                ans += t2 * p2;
            }
            else {
                ans += (seg[i + 1].l - cnt_time) * p2;
                continue;
            }
            cnt_time += t2;
            ans += (seg[i + 1].l - cnt_time) * p3;
        }
    }
    printf("%d\n", ans);
    return 0;
}
