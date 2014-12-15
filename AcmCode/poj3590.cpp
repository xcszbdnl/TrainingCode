#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int MAX_NUMBER = 107;

int dp[MAX_NUMBER][MAX_NUMBER], max_lcm[MAX_NUMBER];
int divisor[MAX_NUMBER], divisor_number, n;



int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}
void getDp() {
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i < MAX_NUMBER; i++) {
        dp[i][1] = i;
    }
    for (int i = 2; i < MAX_NUMBER; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 1; k < i && i - k >= j - 1; k++) {
                int cnt_temp = dp[i - k][j - 1] * k / gcd(dp[i - k][j - 1], k);
                if (cnt_temp > dp[i][j]) {
                    dp[i][j] = cnt_temp;
                }
            }
        }
    }
    for (int i = 1; i < MAX_NUMBER; i++) {
        max_lcm[i] = 0;
        for (int j = 1; j <= i; j++) {
            if (dp[i][j] > max_lcm[i]) {
                max_lcm[i] = dp[i][j];
            }
        }
    }
}

void getDivisor() {
    divisor_number = 0;
    int temp = max_lcm[n];
    for (int i = 2; i * i <= temp; i++) {
        if (temp % i == 0) {
            divisor_number++;
            divisor[divisor_number] = 1;           
            while (temp % i == 0) {
                divisor[divisor_number] *= i;
                temp /= i;
            }
        }
    }
    if (temp != 1) {
        divisor[++divisor_number] = temp;
    }
}
int main() {
    //freopen("input.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    getDp();
    while (test_case--) {
        scanf("%d", &n);
        getDivisor();
        sort(divisor + 1, divisor + 1 + divisor_number);
        int temp = n;
        for (int i = 1; i <= divisor_number; i++) {
            temp -= divisor[i];
        }
        printf("%d", max_lcm[n]);
        for (int i = 1; i <= temp; i++) {
            printf(" %d", i);
        }
        int k = temp + 1;
        for (int i = 1; i <= divisor_number; i++) {
            for (int j = 0; j < divisor[i] - 1; j++) {
                printf(" %d", k + j + 1);
            }
            printf(" %d", k);
            k += divisor[i];
        }
        printf("\n");
    }
    return 0;
}
