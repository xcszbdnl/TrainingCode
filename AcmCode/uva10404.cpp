#include <string.h>
#include <cstdio>


#define MAX_NUMBER 1000005
#define MAX_LENGTH 12

int number[MAX_LENGTH];
int dp[MAX_NUMBER];
int start_number, take_number;

int main() {

    while (scanf("%d", &start_number) != EOF) {
        scanf("%d", &take_number);
        for (int i = 1; i <= take_number; i++) {
            scanf("%d", &number[i]);
        }
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;
        for (int i = 1; i <= start_number; i++) {
            for (int j = 1; j <= take_number; j++) {
                int next_number = i - number[j];
                if (next_number >= 0) {
                    if (!dp[next_number]) {
                        dp[i] = 1;
                        break;
                    }
                }
                dp[i] = 0;
            }
        }
        if (dp[start_number] == 1) {
            printf("Stan wins\n");
        }
        else {
            printf("Ollie wins\n");
        }
    }
    return 0;
}
