#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
const int maxn = 507;

int prime[maxn], prime_num, vis[maxn], maxp;

int matrix[maxn][maxn], n;



void getPrime() {
    memset(vis, 0, sizeof(vis));
    prime_num = 0;
    for (int i = 2; i < maxn; i++) {
        if (!vis[i]) {
            prime[prime_num++] = i;
            for (int j = i * i; j < maxn; j += i) {
                vis[j] = 1;
            }
        }
    }
}


long long getRank() {
    int i = 0, j = 0;
    while (i <= maxp && j < n) {
        int r = i;
        for (int k = i; k <= maxp; k++) {
            if (matrix[k][j]) {
                r = k;
                break;
            }
        }
        if (r != i) {
            for (int k = j; k <= n; k++) {
                swap(matrix[i][k], matrix[r][k]);
            }
        }
        if (matrix[i][j]) {
            for (int k = i + 1; k <= maxp; k++) {
                if (matrix[k][j]) {
                    for (int s = j; s <= n; s++) {
                         matrix[k][s] ^= matrix[i][s];
                    }
                }
            }
            i++;
        }
        j++;
    }
    return 1ll << (n - i);
}

int main() {
    freopen("in.txt", "r", stdin);
    getPrime();
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(matrix, 0, sizeof(matrix));
        scanf("%d", &n);
        maxp = 0;
        for (int i = 0; i < n; i++) {
            long long cnt;
            cin >> cnt;
            for (int j = 0; j < prime_num; j++) {
                while (cnt % prime[j] == 0) {
                    maxp = max(maxp, j);
                    matrix[j][i] ^= 1;
                    cnt /= prime[j];
                }
            }
        }
        long long ans = getRank();
        cout << (ans - 1) << endl;
    }
    return 0;
}
