#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 1010


int longest_subsequence[MAX_NUMBER];
int elements[MAX_NUMBER];


int main() {

    int lenth;
    int i, j, max = 0;
    scanf("%d", &lenth);
    elements[0] = -1;
    memset(longest_subsequence, 0, sizeof(longest_subsequence));
    for (i = 1; i <= lenth; i++) {
        scanf("%d", &elements[i]);
    }
    for (i = 1; i <= lenth; i++) {
        for (j = i - 1; j >= 0; j--) {
            if (elements[i] > elements[j] && longest_subsequence[i] <= longest_subsequence[j]) {
                longest_subsequence[i] = longest_subsequence[j] + 1;
                if (longest_subsequence[i] > max) {
                    max = longest_subsequence[i];
                }
            }
        }
    }
    printf("%d\n", max);
    return 0;
}
