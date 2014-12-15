#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
using namespace std;

const int maxn = 100007;
const long long INF = 50007ll * 50000ll * 50000ll;
set<int> point;
set<int>::iterator pre, last, cnt;
vector<int> point_to_erase;
long long dp[maxn];
int main() {
//    freopen("in.txt", "r", stdin);
    int n, s, k;
    scanf("%d%d%d", &n, &s, &k);
    point.insert(0);
    point.insert(n + 1);
    point.insert(s);
    for (int i = 0; i <= n + 1; i++) {
        dp[i] = INF;
    }
    dp[s] = 0;
    while (k--) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a > 1) {
            a--;
            point.insert(a);
            cnt = point.find(a);
            int loc_1 = *cnt;
            int loc_2, loc_3;
            pre = --cnt;
            cnt++;
            last = ++cnt;
            loc_2 = *pre;
            loc_3 = *last;
            long long temp = dp[loc_2] + loc_1 - loc_2;
            if (temp < dp[loc_1]) {
                dp[loc_1] = temp;
            }
            temp = dp[loc_3] + loc_3 - loc_1;
            if (temp < dp[loc_1]) {
                dp[loc_1] = temp;
            }
            a++;
        }
        if (b < n) {
            b++;
            point.insert(b);
            cnt = point.find(b);
            int loc_1 = *cnt;
            int loc_2, loc_3;
            pre = --cnt;
            cnt++;
            last = ++cnt;
            loc_2 = *pre;
            loc_3 = *last;
            long long temp = dp[loc_2] + loc_1 - loc_2;
            if (temp < dp[loc_1]) {
                dp[loc_1] = temp;
            }
            temp = dp[loc_3] + loc_3 - loc_1;
            if (temp < dp[loc_1]) {
                dp[loc_1] = temp;
            }
            b--;
        }
        point_to_erase.clear();
        for (cnt = point.lower_bound(a); cnt != point.end() && (*cnt) <= b; cnt++) {
            point_to_erase.push_back(*cnt);
        }
        for (int i = 0; i < point_to_erase.size(); i++) {
            dp[point_to_erase[i]] = INF;
            point.erase(point_to_erase[i]);
        }
    }
    long long ans = INF;
    for (int i = 1; i <= n; i++) {
        if (ans > dp[i]) {
            ans = dp[i];
        }
    }
    printf("%I64d\n", ans);
    return 0;
}
