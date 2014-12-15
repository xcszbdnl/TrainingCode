#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>

const int maxn = 100007;

using namespace std;
long long ans = 0;

vector<pair<int, int> > voter;

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        num[a]++;
        voter.push_back(make_pair(b, a));
    }
    sort(voter.begin(), voter.end());
    int low =
    printf("%I64d\n", ans);
    return 0;
}

/*
7
3 49
1 50
1 50
2 50
2 50
3 50
3 50
*/
