#include <iostream>
#include <cstdio>
#include <string.h>
#include <cmath>


#define MAX_NUMBER 50006
#define MAX_LENGTH 105

using namespace std;


int dp[MAX_NUMBER], coin[MAX_LENGTH];


int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        int coin_number;
        scanf("%d", &coin_number);
        int sums  = 0;
        for (int i = 1; i <= coin_number; i++) {
            scanf("%d", &coin[i]);
            sums += coin[i];
        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        dp[sums] = 1;
        for (int i = 1; i <= coin_number; i++) {
            for (int j = 0; j <= sums - coin[i]; j++) {
                if (dp[j] == 1) {
                    dp[j + coin[i]] = 1;
                }
            }
        }
        int ans;
        for (ans = sums / 2; ans >= 0; ans--) {
            if (dp[ans] == 1) {
                break;
            }
        }
        printf("%d\n", sums - 2 * ans);
    }
    return 0;
}
