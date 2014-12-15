#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>


using namespace std;


typedef unsigned long long ULL;

ULL ans, com[50][50];
int n, a, b;

void getCom() {
    for (int i = 1; i < 50; i++) {
        com[i][0] = com[i][i] = 1;
        for (int j = 1; j < i; j++) {
            com[i][j] = com[i - 1][j] + com[i - 1][j - 1];
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    getCom();
    scanf("%d%d%d", &n, &a, &b);
    ans = com[a + n][n];
    ans = ans * com[b + n][n];
    cout << ans << endl;
}
