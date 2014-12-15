/**
 *FILENAME: poj1840.c
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON：2013-2-3
 */

#include <stdio.h>
#include <string.h>

/**
 *DESCRIPTION:
 Using hash to solve it
 */

#define MAX_NUMBER 50
#define MIN_NUMBER -50
#define SHIFT 12500000
char hash[2 * SHIFT + 10];


int main() {
    freopen("input.txt", "r", stdin);
    int a_1, a_2, a_3, a_4, a_5;
    int i, j, k, result;
    int ans = 0;
    memset(hash, 0, sizeof(hash));
    scanf("%d%d%d%d%d",&a_1, &a_2, &a_3, &a_4, &a_5);
    for (i = MIN_NUMBER; i <= MAX_NUMBER; i++) {
        for (j = MIN_NUMBER;j <= MAX_NUMBER; j++) {
            for (k = MIN_NUMBER; k <= MAX_NUMBER; k++) {
                result = a_1 * i * i * i + a_2 * j * j *j + a_3 * k * k * k;
                if (i == 0 || j == 0 || k == 0 || result > 12500000 || result < -12500000) {
                    continue;
                }
                hash[result + SHIFT]++;
            }
        }
    }
    for (i = MIN_NUMBER; i <= MAX_NUMBER; i++) {
        for (j = MIN_NUMBER;j <= MAX_NUMBER; j++) {
            result = -a_4 * i * i * i + -a_5 * j * j * j;
            if (i == 0 || j == 0) {
                continue;
            }
            ans += hash[result + SHIFT];
        }
    }
    printf("%d\n", ans);
    return 0;
}
            
