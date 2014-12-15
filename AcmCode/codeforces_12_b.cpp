#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>


using namespace std;
int s;
char d[100];
int num[20];
int main() {
//    freopen("in.txt", "r", stdin);
    memset(num, 0, sizeof(num));
    scanf("%d%s", &s, d);
//    int len = strlen(s);
    int bob_ans = 0;
    int j = 0;
    while (d[j] == '0') {
        j++;
    }
    if (j > 0 && strlen(d) != 1) {
        printf("WRONG_ANSWER\n");
        return 0;
    }
    for (; j < strlen(d); j++) {
        bob_ans = bob_ans * 10 + d[j] - '0';
    }

    if (s == 0) {
        if (!bob_ans) {
            printf("OK\n");
        }
        else {
            printf("WRONG_ANSWER\n");
        }
        return 0;
    }
    while (s) {
        num[s % 10]++;
        s /= 10;
    }

    int ret = 0;
    for (int i = 1; i < 10; i++) {
        if (num[i]) {
            ret = i;
            num[i]--;
            break;
        }
    }
    for (int i = 0; i < num[0]; i++) {
        ret *= 10;
    }
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < num[i]; j++) {
            ret = ret * 10 + i;
        }
    }
//    printf("%d\n", ret);
    if (ret == bob_ans) {
        printf("OK\n");
    }
    else {
        printf("WRONG_ANSWER\n");
    }
    return 0;
}
