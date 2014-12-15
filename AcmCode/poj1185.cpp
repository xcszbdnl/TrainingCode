#include <cstdio>
#include <string.h>

#define MAX_HEIGHT 105
#define MAX_WIDTH 10
#define MAX_METHOD 70
#define max(a,b) ((a) > (b)) ? (a) : (b)

int height, width;
int map[MAX_HEIGHT];
int num[MAX_HEIGHT], status[MAX_HEIGHT];
int dp[MAX_HEIGHT][MAX_METHOD][MAX_METHOD];
int method;

int judge(int cnt_status) {
    for (int i = 0; i < width; i++) {
        if (cnt_status & (1 << i)) {
            if (cnt_status & (1 << (i + 1))) {
                return 0;
            }
            else if (cnt_status & (1 << (i + 2))) {
                return 0;
            }
        }
    }
    return 1;
}

int getSum(int cnt_status) {
    int ans = 0;
    for (int i = 0; i < width; i++) {
        if (cnt_status & (1 << i)) {
            ans++;
        }
    }
    return ans;
}

void preDeal() {
    for (int i = 0; i < 1 << width; i++) {
        if (judge(i)) {
            num[method] = getSum(i);
            status[method] = i;
            method++;
        }
    }
}

int main() {

    scanf("%d%d", &height, &width);
    for (int i = 0; i < height; i++) {
        char temp[10];
        scanf("%s", temp);
        for (int j = 0; j < width; j++) {
            if (temp[j] == 'H') {
                map[i] |= 1 << j;
            }
        }
    }
    method = 0;
    memset(dp, 0, sizeof(dp));
    preDeal();
    for (int i = 0; i < method; i++) {
        if (!(status[i] & map[0])) {
            dp[0][i][0] = num[i];
        }
    }
    for (int i = 0; i < method; i++) {
        if (!(status[i] & map[1])) {
            for (int j = 0; j < method; j++) {
                if (!(status[i] & status[j])) {
                    dp[1][i][j] = max(dp[1][i][j], dp[0][j][0] + num[i]);
                }
            }
        }
    }
    for (int i = 2; i < height; i++) {
        for (int j = 0; j < method; j++) {
            if (!(status[j] & map[i])) {
                for (int k = 0; k < method; k++) {
                    if (!(status[j] & status[k])) {
                        for (int m = 0; m < method; m++) {
                            if (!(status[j] & status[m])) {
                                dp[i][j][k] = max(dp[i][j][k], dp[i - 1][k][m] + num[j]);
                            }
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < method; i++) {
        for (int j = 0; j < method; j++) {
            ans = max(ans, dp[height - 1][i][j]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
