#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const double INF = 1e+50;
const double eps = 1e-8;
const int maxn = 10000;
long long loc[maxn];
long long dest_x, dest_y;


double dist(long long x) {
    long long cnt_x = dest_x - x;
    long long cnt_y = dest_y;
    cnt_x *= cnt_x;
    cnt_y *= cnt_y;
    return sqrt((cnt_x + cnt_y) * 1.0);
}

int main() {
//    freopen("in.txt", "r", stdin);
    int n, vb, vs;
    scanf("%d%d%d", &n, &vb, &vs);
    double min_ans = INF;
    for (int i = 1; i <= n; i++) {
        scanf("%I64d", &loc[i]);
    }
    scanf("%I64d%I64d", &dest_x, &dest_y);
    int ans_loc;
    double u_dist = INF;
    for (int i = 2; i <= n; i++) {
        int d1 = loc[i];
        double t1 = d1 * 1.0 / vb;
        double d2 = dist(loc[i]);
        double t2 = d2 / vs;
        if (t1 + t2 < min_ans) {
            min_ans = t1 + t2;
            u_dist = t2;
            ans_loc = i;
        }
        else if (fabs(t1 + t2 - min_ans) < eps) {
            if (t2 < u_dist) {
                u_dist = t2;
                ans_loc = i;
            }
        }
    }
    printf("%d\n", ans_loc);
    return 0;
}

