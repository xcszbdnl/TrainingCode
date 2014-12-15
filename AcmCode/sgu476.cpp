#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 10007;
long long dp[maxn];

struct Triple {
    int a, b, c;
};


int main() {
    freopen("in.txt", "r", stdin);
    dp[3] = 1;
    for (int i = 6; i < maxn ; i += 3) {
        dp[i] = dp[i - 3] * i * (i - 1) * (i - 2) / 3 / 2 / (i / 3);
    }
    return 0;
}
