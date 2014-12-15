#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>

const int maxn = 1007;

using namespace std;

char str[maxn];
int val[maxn];
int n, p;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &p);
    scanf("%s", str);
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        val[i + 1] = str[i] - 'a';
    }
    int flag = 0;
    for (int i = len; i >= 1; i--) {
        val[i]++;
        if (val[i] == p) {
            if (i == 1) {
                flag = 1;
                break;
            }
            continue;
        }
        while (val[i] == val[i - 1] || (i >= 3 && val[i] == val[i - 2])) {
            val[i]++;
        }
        if (val[i] == p) {
            continue;
        }
        for (int j = i + 1; j <= len; j++) {
            val[j] = 0;
            while (val[j] == val[j - 1] || (j >= 3 && val[j] == val[j - 2])) {
                val[j]++;
            }
        }
        break;
    }
    if (flag) {
        printf("NO\n");
        return 0;
    }
    for (int i = 1; i <= len; i++) {
        printf("%c", val[i] + 'a');
    }
    printf("\n");
    return 0;
}
