#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 300007;
const int INF = 1000000007ll;
int val[maxn];
map<long long, long long> maps;
long long n, maxval, minval;

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    maxval = 0;
    minval = INF;
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        if (maps.count(x)) {
            maps[x]++;
        }
        else {
            maps[x] = 1;
        }
        maxval = max(maxval, x);
        minval = min(minval, x);
    }
    if (maxval != minval) {
        long long ans = maps[maxval] * maps[minval];
        cout << maxval - minval << " " << ans << endl;
    }
    else {
        long long ans = maps[maxval] * (maps[maxval] - 1) / 2;
        cout << 0 << " " << ans << endl;
    }

    return 0;
}
