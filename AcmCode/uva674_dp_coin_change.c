#include <stdio.h>


#define MAX_NUMBER 7500

int num[MAX_NUMBER];
int coin[5] = {1,5,10,25,50};


int main() {
    int i, j, money;
    num[0] = 1;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < MAX_NUMBER; j++) {
            if (j >= coin[i]) {
                num[j] += num[j - coin[i]];
            }
        }

    }
    while (scanf("%d", &money)) {
        printf("%d\n", num[money]);
    }
    return 0;
}
