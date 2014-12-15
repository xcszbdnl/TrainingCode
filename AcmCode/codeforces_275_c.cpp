#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define INF 1000000000
#define pb push_back
#define itr iterator
#define sz size()
#define mp make_pair

int n;
char ss[50][30];
long long indistinguishable[1<<20];
double dp[1<<20];
double C[21][21];

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &n);

    for (int i = 0; i <= 20; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }

    for (int i = 0; i < n; i++) {
        scanf("%s", ss[i]);
    }

    int len = strlen(ss[0]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (i != j) {
            int same = 0;
            for (int pos = 0; pos < len; pos++) {
                if (ss[i][pos] == ss[j][pos]) {
                    same |= (1<<pos);
                }
            }
            indistinguishable[same] |= (1LL<<i);
        }
    }

    double ans = 0;
    for (int bm = (1<<len)-1; bm >= 0; bm--) {
//        int c = 0;
        for (int i = 0; i < len; i++) {
            if (!(bm & (1<<i)) ) {
//                c++;
                indistinguishable[bm] |= indistinguishable[bm + (1<<i)];
            }
        }

        if (!indistinguishable[bm]) continue;
        ans += 1.0 * __builtin_popcountll(indistinguishable[bm]) / n / C[len][__builtin_popcount(bm)];
    }

    printf("%.15f", ans);
}
