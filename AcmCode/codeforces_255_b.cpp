#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>

using namespace std;
const int maxn = 1007;
const int inf = 0x0f0f0f0f;
priority_queue<long long> row, col;
long long sum_r[1000007], sum_c[1000007];
long long n, m, k, p;
long long val[1007][1007];
int main() {
//    freopen("in.txt", "r", stdin);
    cin >> n >> m >> k >> p;
    for (int i = 1; i <= n; i++) {
        long long row_sum = 0;
        for (int j = 1; j <= m; j++) {
            cin >> val[i][j];
            row_sum += val[i][j];
        }
        row.push(row_sum);
    }
    for (int i = 1; i <= m; i++) {
        long long  col_sum = 0;
        for (int j = 1; j <= n; j++) {
            col_sum += val[j][i];
        }
        col.push(col_sum);
    }
    sum_r[0] = 0;
    for (int i = 1; i <= k; i++) {
        long long temp = row.top();
        sum_r[i] = sum_r[i - 1] + temp;
        row.pop();
        temp -= m * p;
        row.push(temp);
    }
    sum_c[0] = 0;
    for (int i = 1; i <= k; i++) {
        long long temp = col.top();
        sum_c[i] = sum_c[i - 1] + temp;
        temp -= n * p;
        col.pop();
        col.push(temp);
    }
    long long ans = sum_r[k];
    for (int i = 0; i <= k; i++) {
        if (sum_r[i] + sum_c[k - i] - (long long)i * (k - i) * p > ans) {
            ans = sum_r[i] + sum_c[k - i] - i *(k - i) * p;
        }
    }
    cout << ans << endl;
    return 0;
}

