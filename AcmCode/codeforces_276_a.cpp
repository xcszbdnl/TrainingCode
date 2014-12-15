#include <cstdio>
#include <cstring>
#include <iostream>

const int maxn = 100;
using namespace std;

long long l, r;
int str_1[maxn], str_2[maxn], len;
int main() {
//    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    while (n--) {
        cin >> l >> r;
        memset(str_1, 0, sizeof(str_1));
        memset(str_2, 0, sizeof(str_2));
        len = 0;
        if (l == r) {
            cout << l << endl;
            continue;
        }
        while (r) {
            str_1[len++] = r % 2;
            r /= 2;
        }
        int t = 0;
        while (l) {
            str_2[t++] = l % 2;
            l /= 2;
        }
        for (int i = len - 1; i >= 0; i--) {
            if (str_1[i] == 1 && str_2[i] == 0) {
                str_1[i] = 0;
                int flag = 0;
                for (int j = i - 1; j >= 0; j--) {
                    if (str_1[j] == 0) {
                        flag = 1;
                        str_1[j] = 1;
                    }
                }
                if (!flag) {
                    str_1[i] = 1;
                }
                break;
            }
        }
        long long ans = 0;
        for (int i = maxn - 1; i >= 0; i--) {
            if (str_1[i] != 0)  {
                len = i + 1;
                break;
            }
        }
        for (int i = len - 1; i >= 0; i--) {
            ans = ans * 2 + str_1[i];
        }
        cout << ans << endl;
    }
    return 0;
}

