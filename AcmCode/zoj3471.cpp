#include <iostream>
#include <cstdio>
#include <string.h>


#define MAX_NUMBER 2000
#define MAX_ROW 11
#define max(a,b) ((a) > (b)) ? (a) : (b)


int dp[MAX_NUMBER];
int value[MAX_ROW][MAX_ROW];
int atom_number;

int main() {

    while (scanf("%d", &atom_number) != EOF) {
        if (!atom_number) {
            break;
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < atom_number; i++) {
            for (int j = 0; j < atom_number; j++) {
                scanf("%d", &value[i][j]);
            }
        }
        for (int i = 0; i < (1 << atom_number); i++) {
            for (int j = 0; j < atom_number; j++) {
                if (i & (1 << j)) {
                    for (int k = 0; k < atom_number; k++) {
                        if (j != k && (i & (1 << k))) {
                            dp[i] = max(dp[i], dp[i ^ (1 << k)] + value[j][k]);
                        }
                    }
                }
            }
        }
        printf("%d\n", dp[(1 << atom_number) - 1]);
    }
    return 0;
}
