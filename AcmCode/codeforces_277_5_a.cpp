#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>

const int INF = 1000000007;
const int maxn = 3007;

using namespace std;
vector<pair<int, int> >ret;
int n, val[maxn];
int main() {
//    freopen("in.txt", "r", stdin);
    int ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    for (int i = 1; i <= n; i++) {
        int max_num = -INF;
        int loc = 0;
        int flag = 0;
        for (int j = 1; j <= n - i + 1; j++) {
            if (val[j] > max_num) {
                max_num = val[j];
                loc = j;
            }
        }
        swap(val[loc], val[n - i + 1]);
        ret.push_back(make_pair(loc, n - i + 1));
    }
    printf("%d\n", ret.size());
    for (int i = 0; i < ret.size(); i++) {
        printf("%d %d\n", ret[i].first - 1, ret[i].second - 1);
    }
    return 0;
}
