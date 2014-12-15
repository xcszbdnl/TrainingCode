#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 200

int main() {
    freopen("input.txt", "r", stdin);
    int case_number, n_parenth;
    int p_sequence[MAX_NUMBER], matched[MAX_NUMBER], right_parenth[MAX_NUMBER], original_sequence[MAX_NUMBER], match_number[MAX_NUMBER];
    int i, j, left_number, right_number, location, match_start;
    scanf("%d", &case_number);
    while (case_number--) {
        scanf("%d", &n_parenth);
        left_number = right_number = 0;
        memset(original_sequence, 0, sizeof(original_sequence));
        memset(matched, 0, sizeof(matched));
        memset(match_number, 0, sizeof(match_number));
        for (i = 0; i < n_parenth; i++) {
            scanf("%d", &p_sequence[i]);
        }
        for (i = 0; i < n_parenth; i++) {
            left_number = p_sequence[i];
            location = left_number + right_number;
            original_sequence[location] = 1;
            right_parenth[i] = location;
            right_number++;
        }
        for (i = 0; i < n_parenth; i++) {
            match_number[i] = 0;
            match_start = right_parenth[i];
            for (j = match_start - 1; j >= 0; j--) {
                if (original_sequence[j] == 0) {
                    match_number[i]++;
                    if (matched[j] == 0) {
                        matched[j] = 1;
                        break;
                    }
                }
            }
        }
        for (i = 0; i < n_parenth; i++) {
            if (i) {
                printf(" %d", match_number[i]);
            }
            else {
                printf("%d", match_number[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
