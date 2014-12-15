#include <string.h>
#include <iostream>
#include <cstdio>

#define MAX_LENGTH 12
#define MAX_STATUS 5000

using namespace std;


long long dp[MAX_LENGTH][MAX_STATUS];
int width, height;

int judge(int status) {
    int j = 0;
    while (j < width) {
        if (status & (1 << j)) {
            if (j == width - 1 || !(status & (1 << (j + 1)))) {
                return 0;
            }
            j += 2;
        }
        else {
            j++;
        }
    }
    return 1;
}

int isCompatible(int cnt_status, int previous_status) {
    int j = 0;
    while (j < width) {
        if (cnt_status & (1 << j)) {
            if (previous_status & (1 << j)) {
                if (j == width - 1 || !(cnt_status & (1 << (j + 1))) || !(previous_status & (1 << (j + 1)))) {
                    return 0;
                }
                j += 2;
            }
            else {
                j++;
            }
        }
        else {
            if (!(previous_status & (1 << j))) {
                return 0;
            }
            j++;
        }
    }
    return 1;
}

int main() {

    while (scanf("%d%d", &width, &height) != EOF) {
        if (!height && !width) {
            break;
        }
        memset(dp, 0, sizeof(dp));        
        if ((width * height) % 2 != 0) {
            printf("%d\n", 0);
            continue;
        }
        if (width > height) {
            int temp = width;
            width = height;
            height = temp;
        }
        int max_status = 1 << width;
        for (int i = 0; i < max_status; i++) {
            if (judge(i)) {
                dp[1][i] = 1;
            }
        }
        for (int i = 2; i <= height; i++) {
            for (int cnt_status = 0; cnt_status < max_status; cnt_status++) {
                for (int previous_status = 0; previous_status < max_status; previous_status++) {
                    if (dp[i - 1][previous_status] && isCompatible(cnt_status, previous_status)) {
                        dp[i][cnt_status] += dp[i - 1][previous_status];
                    }
                }
            }
        }
        cout << dp[height][max_status - 1] << endl;
    }
    return 0;
}
