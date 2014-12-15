#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>


const int maxn = 1007;
using namespace std;

int maps[maxn][maxn];
int main() {
    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    memset(maps, -1, sizeof(maps));
    for (int i = 1; i <= n; i++) {
        maps[i][i] = 0;
    }
    for (int i = 2; i <= n; i++) {
        maps[i][1] = n - i + 1;
        maps[1][i] = n - i + 1;
        maps[n][i] = i;
        maps[i][n] = i;
    }
    return 0;
}
