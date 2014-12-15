#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

map<long long, long long> maps;
const int maxn = 100007;
const long long INF = 100000000000000000ll;
struct T{
    long long type;
    long long val, pre, c;
};

struct T t[maxn];
long long tot_index[maxn];
int n, m;

long long getAns(long long cnt_x) {
    if (maps.count(cnt_x)) {
        return maps[cnt_x];
    }
    int pre_loc = lower_bound(tot_index + 1, tot_index + 1 + m, cnt_x) - tot_index;
    if (tot_index[pre_loc] > cnt_x) {
        pre_loc--;
    }
    long long temp = cnt_x;
    cnt_x = (cnt_x - tot_index[pre_loc] + 1) % t[pre_loc].pre;
    if (cnt_x == 0) {
        cnt_x += t[pre_loc].pre;
    }
    long long ans = getAns(cnt_x);
//    maps[temp] = ans;
    return ans;
}
int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &m);
    long long cnt_loc = 0;
    for (int i = 1; i <= m; i++) {
        scanf("%I64d", &t[i].type);
        if (t[i].type == 1) {
            scanf("%I64d", &t[i].val);
        }
        else {
            scanf("%I64d%I64d", &t[i].pre, &t[i].c);
        }
        if (t[i].type == 1) {
            tot_index[i] = ++cnt_loc;
            maps[tot_index[i]] = t[i].val;
        }
        else {
            tot_index[i] = cnt_loc + 1;
            cnt_loc += t[i].pre * t[i].c;
        }
//        printf("%d\n", tot_index[i]);
    }
    tot_index[m + 1] = INF;
    scanf("%d", &n);
//    n = 18691;
//    getAns(12031);
    for (int i = 1; i <= n; i++) {
        long long x;
        scanf("%I64d", &x);
        long long ans = getAns(x);
//        long long ans = getAns(i);
//        long long temp = i;
        printf("%I64d ", ans);
    }
    printf("\n");
    return 0;
}
