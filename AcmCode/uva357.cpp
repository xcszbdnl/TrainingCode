#include <iostream>
#include <cstdio>
#include <string.h>

#define MAX_NUMBER 30005
#define MAX_COIN 5

int coin[MAX_COIN] = {1, 5, 10, 25, 50};
long long dp[MAX_NUMBER];


int main() {

    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i < MAX_COIN; i++) {
        for(int j = 0; j < MAX_NUMBER; j++) {
            if (j >= coin[i]) {
                dp[j] += dp[j - coin[i]];
            }
        }
    }
    int cents;
    while (scanf("%d", &cents) != EOF) {
        if (dp[cents] != 1) {
            printf("There are %lld ways to produce %d cents change.\n", dp[cents], cents);
        }
        else {
            printf("There is only 1 way to produce %d cents change.\n", cents);
        }
    }
    return 0; 

}
