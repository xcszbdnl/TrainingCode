#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1000007;
char str_1[maxn], str_2[maxn];
int len_1, len_2;
void dfs(char *s, int &len) {
    int i = len - 1;
    while (i >= 1) {
        if (i > len) {
            len = i;
        }
        if (s[i] == '1' && s[i - 1] == '1') {
            s[i] = '0';
            s[i - 1] = '0';
            s[i + 1] = '1';
            i += 2;
        }
        else {
            i--;
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%s%s", str_1, str_2);
    int len_1 = strlen(str_1);
    int len_2 = strlen(str_2);
    for (int i = 0, j = len_1 - 1; i < j; i++, j--) {
        swap(str_1[i], str_1[j]);
    }
    for (int i = 0, j = len_2 - 1; i < j; i++, j--) {
        swap(str_2[i], str_2[j]);
    }
    dfs(str_1, len_1);
    dfs(str_2, len_2);
    for (int i = len_1 - 1; i >= 0; i--) {
        if (str_1[i] == '1') {
            len_1 = i + 1;
            break;
        }
        else {
            len_1 = 0;
        }
    }
    for (int i = len_2 - 1; i >= 0; i--) {
        if (str_2[i] == '1') {
            len_2 = i + 1;
            break;
        }
        else {
            len_2 = 0;
        }
    }
    if (len_1 < len_2) {
        printf("<\n");
    }
    else if (len_1 > len_2) {
        printf(">\n");
    }
    else {
        int flag = 0;
        for (int i = len_1 - 1; i >= 0; i--) {
            if (str_1[i] > str_2[i]) {
                flag = 1;
                break;
            }
            else if (str_1[i] < str_2[i]) {
                flag = -1;
                break;
            }
        }
        if (flag == -1) {
            printf("<\n");
        }
        else if (flag == 1) {
            printf(">\n");
        }
        else {
            printf("=\n");
        }
    }
    return 0;
}
