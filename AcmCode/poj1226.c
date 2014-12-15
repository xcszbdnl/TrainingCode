#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 105

char word[MAX_NUMBER][MAX_NUMBER];
char subsequence[MAX_NUMBER];
char reverse_subsequence[MAX_NUMBER];
int next[MAX_NUMBER];
int next_reverse[MAX_NUMBER];
int subsequence_lenth;

void computePreffix() {
    int i, k;
    next[0] = -1;
    k = -1;
    for (i = 1; i < subsequence_lenth; i++) {
        while (k != -1 && subsequence[k + 1] != subsequence[i]) {
            k = next[k];
        }
        if (subsequence[k + 1] == subsequence[i]) {
            k++;
        }
        next[i] = k;
    }
    next_reverse[0] = -1;
    k = -1;
    for (i = 0; i < subsequence_lenth; i++) {
        while (k != -1 && reverse_subsequence[k + 1] != reverse_subsequence[i]) {
            k = next_reverse[k];
        }
        if (reverse_subsequence[k + 1] == reverse_subsequence[i]) {
            k++;
        }
        next[i] = k;
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    int test_case, i ,j, k, m, flag, ans;
    int word_number, min_lenth = MAX_NUMBER;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &word_number);
        for (i = 0; i < word_number; i++) {
            scanf("%s", word[i]);
            lenth = strlen(word[i]);
            if (lenth < min_lenth) {
                min_lenth = lenth;
            }
        }
        flag = 1;
        for (i = min_lenth; i >= 1 && !flag; i--) {
            for (j = 0; j + min_lenth <= strlen(word[0]) && !flag; j++) {
                location = j + min_lenth;
                for (k = 0; k < i; k++) {
                    subsequence[k] = word[0][j + k];
                }
                subsequence[k] = '\0';
                reverseString(subsequence, reverse_subsequence);
                subsequence_lenth = i;]
                computePreffix();
                for (m = 0; m < word_number; m++) {
                    if (!compete(word[i])) {
                        break;
                    }
                }
                if (m == word_number) {
                    flag = 1;
                    ans = subsequence_lenth;
                }
            }
        }
        printf("%d\n", ans);
    }
    
}
