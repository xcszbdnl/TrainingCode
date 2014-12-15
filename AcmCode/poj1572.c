#include <stdio.h>
#include <string.h>

#define MAX_TEXT_LENTH 260
#define MAX_SUB_LENTH 90
#define MAX_REPLACE_NUMBER 10

char replace_string[MAX_REPLACE_NUMBER][MAX_SUB_LENTH];
char find_string[MAX_REPLACE_NUMBER][MAX_SUB_LENTH];
char text_string[MAX_TEXT_LENTH];
int replace_number;

void solve() {
    int i, j, k;
    int flag, lenth_find_string, lenth_replace_string, distance, lenth_text;
    for (k = 0; k < replace_number; k++) {
        flag = 1;
        while (flag) {
            for (i = 0; text_string[i]; i++) {
                for (j = 0; find_string[k][j]; j++) {
                    if (find_string[k][j] != text_string[i + j]) {
                        break;
                    }
                }
                if (find_string[k][j] != '\0') {
                    flag = 0;
                }
                else {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                lenth_find_string = strlen(find_string[k]);
                lenth_replace_string = strlen(replace_string[k]);
                distance = lenth_find_string - lenth_replace_string;
                lenth_text = strlen(text_string);
                if (distance > 0) {
                    for (j = i + lenth_find_string; j <= lenth_text; j++) {
                        text_string[j - distance] = text_string[j];
                    }
                }
                else if (distance < 0) {
                    for (j = lenth_text; j >= i + lenth_find_string; j--) {
                        text_string[j - distance] = text_string[j];
                    }
                }
                for (j = 0; j < lenth_replace_string; j++) {
                    text_string[i + j] = replace_string[k][j];
                }
            }
        }
    }
    printf("%s\n", text_string);
}

int main() {

    int i;
    while (scanf("%d", &replace_number) != EOF) {
        if (!replace_number) {
            break;
        }
        getchar();
        for (i = 0; i < replace_number; i++) {
            gets(find_string[i]);
            gets(replace_string[i]);
        }
        gets(text_string);
        solve();
    }
}
