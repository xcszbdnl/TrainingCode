#include <stdio.h>
#include <string.h>

#define MAX_LENTH 305
#define WORD_LENTH 30
#define MAX_WORDS 610

char message[MAX_LENTH];
char dictionary[MAX_WORDS][WORD_LENTH];
int dp[MAX_LENTH];

int main() {

    int message_lenth, word_number;
    int word_lenth, current_pos;
    int i, j, k;
    scanf("%d%d", &word_number, &message_lenth);
    scanf("%s", message);
    for (i = 0; i < word_number; i++) {
        scanf("%s", dictionary[i]);
    }
    for (i = message_lenth - 1; i >= 0; i--) {
        dp[i] = dp[i + 1] + 1;
        for (j = 0; j <= word_number; j++) {
            if (dictionary[j][0] == message[i]) {
                word_lenth = strlen(dictionary[j]);
                current_pos = i;
                k = 0;
                while (current_pos < message_lenth && k < word_lenth) {
                    if (message[current_pos] == dictionary[j][k]) {
                        k++;
                    }
                    current_pos++;
                }
                if (k == word_lenth && dp[i] > (dp[current_pos] + (current_pos - i) - word_lenth)) {
                    dp[i] = dp[current_pos] + (current_pos - i) - word_lenth ;
                }
            }
        }
    }
    printf("%d\n", dp[0]);
    return 0;
}

