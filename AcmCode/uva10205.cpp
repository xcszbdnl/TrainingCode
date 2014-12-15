#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 110;
const int MAX_LENGTH = 60;


int shuffle[MAX_NUMBER][MAX_LENGTH];
int k_number[MAX_NUMBER];
int ans[MAX_LENGTH], temp[MAX_LENGTH];
int n, k;
char values[][20] = {"Jack", "Queen", "King", "Ace"};
char suits[][20] = {"Clubs", "Diamonds", "Hearts", "Spades"};

int main() {


    int test_case;
    scanf("%d", &test_case);
    int first = 0;
    while (test_case--) {
        if (first) {
            printf("\n");
        }
        scanf("%d", &n);
        for (int i = 1; i <= 52; i++) {
            ans[i] = i - 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= 52; j++) {
                scanf("%d", &shuffle[i][j]);
            }
        }
        getchar();
        char operation[10];
        k = 0;
        while (gets(operation)) {
            if (operation[0] == '\n' || operation[0] == '\0') {
                break;
            }
            k_number[k] = 0;
            for (int i = 0; operation[i]; i++) {
                k_number[k] = k_number[k] * 10 + operation[i] - '0';
            }
            k++;
        }
        for (int i = 0; i < k; i++) {
            int cnt_shuffle = k_number[i];
            memcpy(temp, ans, sizeof(ans));
            for (int j = 1; j <= 52; j++) {
                temp[j] = ans[shuffle[cnt_shuffle][j]];
            }
            memcpy(ans, temp, sizeof(ans));
        }
        for (int i = 1; i <= 52; i++) {
            int cnt_card = ans[i];
            int cnt_value = cnt_card % 13;
            int cnt_suit = cnt_card / 13;
            if (cnt_value >= 9) {
                printf("%s", values[cnt_value - 9]);
            }
            else {
                printf("%d", cnt_value + 2);
            }
            printf(" of %s\n", suits[cnt_suit]);
        }
        first = 1;
    }
    return 0;
}
