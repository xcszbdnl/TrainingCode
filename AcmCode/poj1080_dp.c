#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 105
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int max_score[MAX_NUMBER][MAX_NUMBER];
char string_1[MAX_NUMBER];
char string_2[MAX_NUMBER];
int getScore(char ch1, char ch2) {
    switch(ch1) {
    case 'A':
        switch(ch2) {
        case 'A':
            return 5;
        case 'C':
            return -1;
        case        'G':
            return -2;
        case        'T':
            return -1;
        case        '-':
            return -3;
        }
    case 'C':
        switch(ch2) {
        case        'A':
            return -1;
        case        'C':
            return 5;
        case        'G':
            return -3;
        case        'T':
            return -2;
        case        '-':
            return -4;
        }
    case 'G':
        switch(ch2) {
        case        'A':
            return -2;
        case        'C':
            return -3;
        case        'G':
            return 5;
        case        'T':
            return -2;
        case        '-':
            return -2;
        }
    case 'T':
        switch(ch2) {
        case        'A':
            return -1;
        case        'C':
            return -2;
        case    'G':
            return -2;
        case'T':
            return 5;
        case        '-':
            return -1;
        }
    case '-':
        switch(ch2) {
        case    'A':
            return -3;
        case        'C':
            return -4;
        case        'G':
            return -2;
        case        'T':
            return -1;
        case        '-':
            return 0;
        }
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    int test_case;
    int lenth_1, lenth_2, step_1, step_2, step_3, max_step;
    int i, j;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(max_score, 0, sizeof(max_score));
        scanf("%d", &lenth_1);
        scanf("%s", string_1);
        scanf("%d", &lenth_2);
        scanf("%s", string_2);
        for (i = 1; i <= lenth_1; i++) {
            max_score[i][0] = max_score[i - 1][0] + getScore(string_1[i - 1], '-');
        }
        for (i = 1; i <= lenth_2; i++) {
            max_score[0][i] = max_score[0][i - 1] + getScore('-', string_2[i - 1]);
        }
        for (i = 1; i <= lenth_1; i++) {
            for (j = 1; j <= lenth_2; j++) {
                step_1 = max_score[i - 1][j] + getScore('-', string_2[j - 1]);
                step_2 = max_score[i][j - 1] + getScore(string_1[i - 1], '-');
                step_3 = max_score[i - 1][j - 1] + getScore(string_1[i - 1], string_2[j - 1]);
                max_step = MAX(step_1, step_2);
                max_step = MAX(step_3, max_step);
                max_score[i][j] = max_step;
            }
        }
        printf("%d\n", max_score[lenth_1][lenth_2]);
    }
    return 0;
}
