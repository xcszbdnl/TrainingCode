#include <stdio.h>


#define MAX_NUMBER 101


int group_1[MAX_NUMBER];
int group_2[MAX_NUMBER];
int group_3[MAX_NUMBER];


int main() {

    int numbers, positive, negative, point_1, point_2, point_3, one_negative, input_number;
    int i;
    scanf("%d", &numbers);
    positive = negative = point_1 = point_2 = point_3 = 0;
    for (i = 0; i < numbers; i++) {
        scanf("%d", &input_number);
        if (input_number == 0) {
            group_3[point_3++] = input_number;
        }
        else if (input_number < 0) {
            group_2[negative++] = input_number;
        }
        else {
            group_1[positive++] = input_number;
        }
    }
    if (negative % 2 == 0) {
        group_3[point_3++] = group_2[--negative];
    }
    if (positive == 0) {
        group_1[positive++] = group_2[--negative];
        group_1[positive++] = group_2[--negative];
    }
    printf("%d", negative);
    for (i = 0; i < negative; i++) {
        printf(" %d", group_2[i]);
    }
    printf("\n%d", positive);
    for (i = 0; i < positive; i++) {
        printf(" %d", group_1[i]);
    }
    printf("\n%d", point_3);
    for (i = 0; i < point_3; i++) {
        printf(" %d", group_3[i]);
    }
    printf("\n");
    return 0;
     
}
