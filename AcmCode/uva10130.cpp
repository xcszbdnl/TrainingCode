#include <string.h>
#include <cstdio>

#define MAX_NUMBER 5000
#define MAX_PEOPLE 1000
#define max(a,b) ((a) > (b)) ? (a) : (b)

int dp[MAX_NUMBER];
int value[MAX_PEOPLE], weight[MAX_PEOPLE], people[MAX_PEOPLE];
int object_number, people_number, max_weight;

void zeroOnePack(int object_value, int object_weight) {
    for (int capacity = max_weight; capacity >= object_weight; capacity--) {
        dp[capacity] = max(dp[capacity], dp[capacity - object_weight] + object_value);
    }
}

void solve() {
    for (int i = 1; i <= object_number; i++) {
        zeroOnePack(value[i], weight[i]);
    }
}

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &object_number);
        for (int i = 1; i <= object_number; i++) {
            scanf("%d%d", &value[i], &weight[i]);
        }
        scanf("%d", &people_number);
        max_weight = 0;
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= people_number; i++) {
            scanf("%d", &people[i]);
            if (max_weight < people[i]) {
                max_weight = people[i];
            }
        }
        solve();
        int ans = 0;
        for (int i = 1; i <= people_number; i++) {
            ans += dp[people[i]];
        }
        printf("%d\n", ans);
    }
    return 0;
}
