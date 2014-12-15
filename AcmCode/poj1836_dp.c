#include <stdio.h>

#define MAX_NUMBER 1100

double height[MAX_NUMBER];
int ascending[MAX_NUMBER];
int descending[MAX_NUMBER];


int main() {

    int soldier_number;
    int i, j;
    int max_lenth = 0;
    scanf("%d", &soldier_number);
    for (i = 1; i <= soldier_number; i++) {
        scanf("%lf", &height[i]);
    }
    for (i = 1; i <= soldier_number; i++) {
        ascending[i] = descending[i] = 1;
    }
    for (i = 2; i <= soldier_number; i++) {
        for (j = i - 1; j >= 0; j--) {
            if (height[i] > height[j] && ascending[i] < ascending[j] + 1) {
                ascending[i] = ascending[j] + 1;
            }
        }
    }
    for (i = soldier_number - 1; i >= 1; i--) {
        for (j = i + 1; j <= soldier_number; j++) {
            if (height[i] > height[j] && descending[i] < descending[j] + 1)  {
                descending[i] = descending[j] + 1;
            }
        }
    }
    for (i = 1; i <= soldier_number; i++) {
        for (j = i + 1; j <= soldier_number; j++) {
            if (max_lenth < ascending[i] + descending[j]) {
                max_lenth = ascending[i] + descending[j];
            }
        }
    }
    printf("%d\n", soldier_number - max_lenth);
    return 0;
}
