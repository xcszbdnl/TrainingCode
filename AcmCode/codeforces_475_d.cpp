#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;
const int maxn = 100007;
map<int ,long long> maps[2], ans;
map<int, long long>::iterator it;
int a[maxn], n;

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
        scanf("%d", &a[i]);
    }
    maps[0].clear();
    maps[1].clear();
    int flag = 0;
    for (int i = 1; i <= n; i++) {
        maps[!flag].clear();
        maps[!flag][a[i]]++;
        for (it = maps[flag].begin(); it != maps[flag].end(); it++) {
            int tmp = it->first;
            long long num = it->second;
            int cnt_gcd = gcd(a[i], tmp);
            maps[!flag][cnt_gcd] += num;
        }
        for (it = maps[!flag].begin(); it != maps[!flag].end(); it++) {
            int tmp = it->first;
            long long num = it->second;
            ans[tmp] += num;
        }
        flag = !flag;
    }
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int x;
        scanf("%d", &x);
        printf("%I64d\n", ans[x]);
    }
    return 0;
}

