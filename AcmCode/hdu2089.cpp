#include <iostream>
#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 15;
int dp[MAX_NUMBER][MAX_NUMBER];
int left_bound, right_bound;

void getDp() {
    dp[0][0] = 1;
    for (int i = 1; i < MAX_NUMBER; i++) {
        dp[i][0] = dp[i - 1][0] * 9 - dp[i - 1][1];
        dp[i][1] = dp[i - 1][0];
        dp[i][2] = dp[i - 1][2] * 10 + dp[i - 1][1] + dp[i - 1][0];
    }
}
int cal(int cnt_number) {
    int length = 0;
    int temp[MAX_NUMBER];
    memset(temp, 0, sizeof(temp));
    int n = cnt_number;
    temp[0] = 0;
    while (cnt_number) {
        temp[++length] = cnt_number % 10;
        //printf("temp:%d\n", temp[length]);
        cnt_number /= 10;
    }
    int flag = 0;
    int ans = 0;
    for (int i = length; i >= 0; i--) {
        ans += dp[i - 1][2] * temp[i];
        //printf("dp[%d][2]:%d\n", i - 1, dp[i - 1][2]);
        if (!flag && temp[i] > 4) {
            ans += dp[i - 1][0];
        }
        if (!flag && temp[i] == 4) {
            if (i >= 2) {
                ans += dp[i - 2][0] * temp[i - 1];
            }
            else {
                ans += 1;
            }
        }
        if (!flag && temp[i] > 6) {
            ans += dp[i - 1][1];
        }
        if (!flag && temp[i + 1] == 6 && temp[i] >= 2) {
            ans += dp[i][1];
        }
        if (flag) {
            ans += dp[i - 1][0] * temp[i];
        }
        if (temp[i] == 4 || (temp[i + 1] == 6 && temp[i] == 2)) {
            flag = 1;
        }
        //printf("ans:%d\n", ans);
    }
    return n - ans;
}
int main() {
    //freopen("input.txt", "r", stdin);
    getDp();
	while (scanf("%d%d", &left_bound, &right_bound) != EOF) {
        if (!left_bound && !right_bound) {
            break;
        }
        int right = cal(right_bound);
        //printf("right:%d\n", right);
        int left = 0;
        if (left_bound >= 0) {
            left = cal(left_bound - 1);
        }
        int ans = right - left;
        //printf("%d %d\n", right, left);
		printf("%d\n", ans);
	}
	return 0;
}
