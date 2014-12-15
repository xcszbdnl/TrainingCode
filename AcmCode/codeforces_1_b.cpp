#include <cstdio>
#include <cstring>

const int maxn = 10007;

char input[maxn];
int ans[maxn];

void solve1() {
    int i;
    int column_number = 0;
//    printf("%s\n", input);
    for (i = 0; i < strlen(input); i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            column_number = column_number * 26 + input[i] - 'A' + 1;
        }
        else {
            break;
        }
    }
    int row_number = 0;
    for (; i < strlen(input); i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            row_number = row_number * 10 + input[i] - '0';
        }
    }
    printf("R%dC%d\n", row_number, column_number);
}

void solve2() {
    int i;
    int row_number = 0;
    for (i = 1; input[i] != 'C'; i++) {
        row_number = row_number * 10 + input[i] - '0';
    }
    int column_number = 0;
//    printf("%d\n", row_number);
    int len = 0;
    i++;
    for (; i < strlen(input); i++) {
        column_number = column_number * 10 + input[i] - '0';
    }
//    printf("%d\n", column_number);
    while (column_number) {
        column_number--;
        ans[len++] = column_number % 26;
        column_number /= 26;
    }
    for (int i = len - 1; i >= 0; i--) {
        printf("%c", 'A' + ans[i]);
    }
    printf("%d\n", row_number);
}

bool hasDigit(int loc_c) {
    for (int i = 1; i < loc_c; i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            return 1;
        }
    }
    return 0;
}
int main() {
//    freopen("input.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%s", input);
        int loc_c, length, flag;
        length = strlen(input);
        flag = 0;
        if (input[0] == 'R') {
            for (int i = length - 1; i >= 0; i--) {
                if (input[i] == 'C') {
                    loc_c = i;
                    flag = 1;
                    break;
                }
            }
            if (flag && loc_c - 0 > 1 && hasDigit(loc_c)) {
                solve2();
            }
            else {
                solve1();
            }
        }
        else {
            solve1();
        }
    }
    return 0;
}
