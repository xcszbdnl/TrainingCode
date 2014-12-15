#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 5001

char input[MAX_NUMBER];
short minimal_number[MAX_NUMBER][MAX_NUMBER];

int main() {

    int lenth;
    int i, j, calculate_lenth;
    scanf("%d", &lenth);
    memset(minimal_number, 0, sizeof(minimal_number));
    scanf("%s", input);
    for (calculate_lenth = 1; calculate_lenth < lenth; calculate_lenth++) {
        for (i = 0; i + calculate_lenth < lenth; i++) {
            if (input[i] == input[i + calculate_lenth]) {
                minimal_number[i][i + calculate_lenth] = minimal_number[i + 1][i + calculate_lenth - 1];
            }
            else {
                if (minimal_number[i + 1][i + calculate_lenth] < minimal_number[i][i + calculate_lenth - 1]) {
                    minimal_number[i][i + calculate_lenth] = minimal_number[i + 1][i + calculate_lenth] + 1;
                }
                else {
                    minimal_number[i][i + calculate_lenth] = minimal_number[i][i + calculate_lenth - 1] + 1;
                }
            }
        }
    }
    printf("%d\n", minimal_number[0][lenth - 1]);
    return 0;
}
