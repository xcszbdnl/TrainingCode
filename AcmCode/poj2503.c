/**
 *FILENAME: poj2503.c
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2013-2-4
 */

#include <stdio.h>
#include <string.h>
#define MAX_NUMBER 100006
#define PRIME 99983

struct Words {
    char english_word[11];
    char foreign_word[11];
};

struct Words input_word[MAX_NUMBER];

int head[PRIME];
int next[MAX_NUMBER];
    
    

int BKDRhash(char *s) {
    int etc = 131;
    int i, hash_code = 0;
    while (*s) {
        hash_code = hash_code * etc + *s++;
    }
    hash_code = hash_code & 0x7FFFFFFF;
    return hash_code % PRIME;
}

int main() {
    freopen("input.txt", "r", stdin);
    int i, lenth, hash_code, j;
    char translate_word[11];
    memset(head, -1, sizeof(head));
    memset(next, -1, sizeof(next));
    for (i = 0; i < MAX_NUMBER; i++) {
        input_word[i].english_word[0] = getchar();
        if (input_word[i].english_word[0] == '\n') {
            break;
        }
        scanf("%s", input_word[i].english_word + 1);
        scanf("%s", input_word[i].foreign_word);
        getchar();
        hash_code = BKDRhash(input_word[i].foreign_word);
        next[i] = head[hash_code];
        head[hash_code] = i;
    }
    lenth = i - 1;
    while (scanf("%s", translate_word) != EOF) {
        hash_code = BKDRhash(translate_word);
        for (j = head[hash_code]; j != -1; j = next[j]) {
            if (strcmp(input_word[j].foreign_word, translate_word) == 0) {
                break;
            }
        }
        if (j == -1) {
            printf("eh\n");
        }
        else {
            printf("%s\n", input_word[j].english_word);
        }
    }
    return 0;
}
