#include <string.h>
#include <cstdio>
#include <algorithm>

using namespace std;

#define min(a,b) ((a) > (b)) ? (b) : (a)
const int MAX_NUMBER = 2003;
long long original[MAX_NUMBER], ordered[MAX_NUMBER];
long long dp[MAX_NUMBER][MAX_NUMBER];
int number;

long long inteAbs(long long cnt_integer) {
    if (cnt_integer > 0) {
        return cnt_integer;
    }
    else {
        return -cnt_integer;
    }
}

int main() {

    scanf("%d", &number);
    for (int i = 1; i <= number; i++) {
        scanf("%d", &original[i]);
        ordered[i] = original[i];
    }
    sort(ordered + 1, ordered + number + 1);
    for (int i = 1; i <= number; i++) {
        dp[1][i] = inteAbs(original[1] - ordered[i]);
    }
    for (int i = 2; i <= number; i++) {
        int min_cost = dp[i - 1][1];
        for (int k = 1; k <= number; k++) {
            min_cost = min(dp[i - 1][k], min_cost);
            dp[i][k] = min_cost + inteAbs(original[i] - ordered[k]);
        }
    }
    int min_ans = dp[number][1];
    for (int i = 1; i <= number; i++) {
        if (min_ans > dp[number][i]) {
            min_ans = dp[number][i];
        }
    }
    printf("%d\n", min_ans);
    return 0;
}
