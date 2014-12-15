#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 2007;
const int p = 100007;
const int INF = 1000000007;
long long dp[maxn];

int maps[maxn][maxn];
int prime_num, prime[p], vis[p];
int k, n, start;
vector<int> depth[maxn];


void output() {
    for (int i = 1; i <= start; i++) {
        for (int j = 1; j <= start; j++) {
            if (maps[i][j]) {
                printf("Y");
            }
            else {
                printf("N");
            }
        }
        printf("\n");
    }
}

void getAllPrime() {
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= sqrt(p * 1.0); i++) {
        if (!vis[i]) {
            for (int j = i + i; j < p; j += i) {
                vis[j] = 1;
            }
        }
    }
    prime_num = 0;
    for (int i = 2; i < p; i++) {
        if (!vis[i]) {
            prime[++prime_num] = i;
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    getAllPrime();
    scanf("%d", &k);
    memset(maps, 0, sizeof(maps));
    start = 4;
    depth[1].push_back(1);
    depth[2].push_back(3);
    depth[2].push_back(4);
    maps[1][3] = maps[3][1] = maps[1][4] = maps[4][1] = 1;
    for (int i = 3; i <= 32; i++) {
        for (int j = 0; j < depth[i - 1].size(); j++) {

        }
    }
    printf("%d\n", start);
    output();
    return 0;
}
