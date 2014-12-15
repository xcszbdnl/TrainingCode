/**
 *FILENAME:poj3274.c
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2012-2-2
 */

#include <stdio.h>
#include <string.h>
#define MAX_NUMBER 100005
#define PRIME 99983
/**
 *DESCRIPTION:
 Static array to implement the hash function;
 */
int bit_feature[MAX_NUMBER][32], partial_sum[MAX_NUMBER][32];
int head[PRIME], next[MAX_NUMBER];

int hashCode(int *array, int lenth) {
    int i, hash_code;
    for (i = 0, hash_code = 0; i < lenth; i++) {
        hash_code = ((hash_code << 2) + (array[i] >> 4)) ^ (array[i] << 10);
    }
    hash_code = hash_code % PRIME;
    if (hash_code < 0) {
        hash_code += PRIME;
    }
    return hash_code;
}

int main() {
    freopen("input.txt","r",stdin);
    int cows_number, feature_number, feature, hash_code, ans = 0;
    int i, j, k;
    scanf("%d%d",&cows_number, &feature_number);
    if (cows_number == 1) {
        printf("1\n");
        return 0;
    }
    memset(head, -1, sizeof(head));
    memset(next, -1, sizeof(next));
    head[0] = 0; next[0] = -1;
    for (i = 1; i <= cows_number; i++) {
        scanf("%d", &feature);
        for (j = 0; j < feature_number; j++) {
            bit_feature[i][j] = feature % 2;
            partial_sum[i][j] += partial_sum[i - 1][j] + bit_feature[i][j];
            feature = feature >> 1;
        }
        for (k = feature_number - 1; k >= 0; k--) {
            partial_sum[i][k] = partial_sum[i][k] - partial_sum[i][0];
        }
        hash_code = hashCode(partial_sum[i], feature_number);
        for (k = head[hash_code]; k != -1; k = next[k]) {
            for (j = 0; j < feature_number; j++) {
                if (partial_sum[k][j] != partial_sum[i][j]) {
                    break;
                }
            }
            if (j == feature_number) {
                break;
            }
        }
        if (k == -1) {
            next[i] = head[hash_code];
            head[hash_code] = i;
        }
        else {
            if (ans < i - k) {
                ans = i - k;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
