#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

const int maxn = 500007;

using namespace std;

struct S {
    int a, b;
};

int n, sums[maxn], num[maxn], p;
map<pair<int, int>, int> maps;
map<pair<int, int>, int>::iterator it;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a > b) {
            swap(a, b);
        }
        num[a]++;
        num[b]++;
        maps[make_pair(a, b)]++;
    }
    long long ans = 0;
    for (it = maps.begin(); it != maps.end(); it++) {
        int a, b;
        a = (it->first).first;
        b = (it->first).second;
        if (num[a] + num[b] >= p && num[a] + num[b] - it->second < p) {
            ans -= 2;
        }
    }
    for (int i = 1; i <= n; i++) {
        sums[num[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        sums[i] += sums[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        int x = p - num[i];
        int cnt_num = sums[n];
        if (x > 0) {
            cnt_num -= sums[x - 1];
        }
        if (num[i] + num[i] >= p) {
            ans--;
        }
        ans += cnt_num;
    }
    ans /= 2;
    printf("%I64d\n", ans);
    return 0;
}

/*
10 0
1 2
2 3
1 2
1 2
2 3
4 5
6 7
8 9
9 10
10 2
*/
