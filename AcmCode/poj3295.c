#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER 120
#define SYMBOL_NUMBER 5

int current_symbol;
char symbols[MAX_NUMBER];
int state[5];

int testTrue() {
    char q = symbols[current_symbol++];
    switch(q) {
    case 'K':
        return testTrue() & testTrue();
        break;
    case 'A':
        return testTrue() | testTrue();
        break;
    case 'N':
        return !testTrue();
        break;
    case 'C':
        return !testTrue() | testTrue();
        break;
    case 'E':
        return testTrue() == testTrue();
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
        return state[q - 'p'];
        break;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int i, j, flag, test_true;
    while (scanf("%s", symbols) != EOF) {
        if (symbols[0] == '0') {
            break;
        }
        int flag = 1;
        for (state[0] = 0; state[0] < 2 && flag; state[0]++) {
            for (state[1] = 0; state[1] < 2 && flag; state[1]++) {
                for (state[2] = 0; state[2] < 2 && flag; state[2]++) {
                    for (state[3] = 0; state[3] < 2 && flag; state[3]++) {
                        for (state[4] = 0; state[4] < 2 && flag; state[4]++) {
                            current_symbol = 0;
                            if (!testTrue()) {
                                flag = 0;
                            }
                        }
                    }
                }
            }
        }
        if (flag) {
            printf("tautology\n");
        }
        else {
            printf("not\n");
        }
    }
    return 0;
}
