#include <string.h>
#include <cstdio>

#define MAX_NUMBER 10000

int dp[MAX_NUMBER];
int track[MAX_NUMBER], pre[MAX_NUMBER];
int track_number, total_length;

void printPath(int cnt_length) {
    if (cnt_length == 0) {
        return ;
    }
    else {
        int pre_number = pre[cnt_length];
        printPath(cnt_length - track[pre_number]);
        printf("%d ", track[pre_number]);
    }
    
}

int main() {

    while (scanf("%d%d", &total_length, &track_number) != EOF) {
        for (int i = 1; i <= track_number; i++) {
            scanf("%d", &track[i]);
        }
        memset(dp, 0, sizeof(dp));
        memset(pre, -1, sizeof(pre));
        dp[0] = 1;
        for (int i = 1; i <= track_number; i++) {
            for (int j = total_length; j >= track[i]; j--) {
                if (dp[j - track[i]] == 1) {
                    dp[j] = 1;
                    if (pre[j] == -1) {
                        pre[j] = i;
                    }
                }
            }
        }
        int i;
        for (i = total_length; i >= 1; i--) {
            if (dp[i] == 1) {
                break;
            }
        }
        printPath(i);
        printf("sum:%d\n", i);
    }
    return 0;
}
