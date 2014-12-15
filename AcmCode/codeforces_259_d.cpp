#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
const int INF = 10000007;
int dp[107][1 << 17], ans[107][1 << 17];
int vis[70], prime[70], prime_num, prime_factor[70];
int n, val[107];
void getPrime() {
    memset(vis, 0, sizeof(vis));
    prime_num = 0;
    for (int i = 2; i < 70; i++) {
        if (!vis[i]) {
            prime[prime_num++] = i;
            for (int j = i * i; j < 70; j += i) {
                vis[j] = 1;
            }
        }
    }
}


void getFactor() {
    memset(prime_factor, 0, sizeof(prime_factor));
    for (int i = 1; i <= 60; i++) {
        for (int j = 0; j < prime_num; j++) {
            if ((i % prime[j]) == 0) {
                prime_factor[i] |= (1 << j);
            }
        }
    }
}

void printAns(int cnt_loc, int cnt_state) {
    if (cnt_loc >= 1) {
        printAns(cnt_loc - 1, cnt_state ^ (prime_factor[ans[cnt_loc][cnt_state]]));
        printf("%d ", ans[cnt_loc][cnt_state]);
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    getPrime();
    prime_num = 16;
    getFactor();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    int max_bit = (1 << prime_num);
    for (int i = 0; i <= n; i++) {
        for (int s = 0; s < max_bit; s++) {
            dp[i][s] = INF;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k < 60; k++) {
            int x = (~prime_factor[k]) & (max_bit - 1);
            for (int s = x; ; s = (s - 1) & x) {
                if (dp[i - 1][s] + abs(val[i] - k) < dp[i][s | prime_factor[k]]) {
                    dp[i][s | prime_factor[k]] = dp[i - 1][s] + abs(val[i] - k);
                    ans[i][s | prime_factor[k]] = k;
                }
                if (s == 0) {
                    break;
                }
            }
        }
    }
    int min_ans = -1;
    int ans_state;
    for (int i = 0; i < max_bit; i++) {
        if (min_ans == -1 || dp[n][i] < min_ans) {
            min_ans = dp[n][i];
            ans_state = i;
        }
    }
    printAns(n, ans_state);
    return 0;
}
