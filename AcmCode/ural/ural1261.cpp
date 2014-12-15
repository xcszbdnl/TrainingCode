#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 100;
long long n;
int three[maxn];
int ans[maxn];
int main() {
//    freopen("in.txt", "r", stdin);
    memset(three, 0, sizeof(three));
    cin >> n;
    int cnt = 0;
    long long tmp = n;
    while (tmp) {
        three[cnt++] = tmp % 3;
        tmp /= 3;
    }
    int pre = 0;
    int flag = 0;
    int num = 0;
    for (int i = 0; i < cnt; i++) {
        if (pre == 0) {
            if (three[i] == 0) {
                ans[i] = 0;
            }
            else if (three[i] == 1) {
                ans[i] = 0;
            }
            else if (three[i] == 2) {
                ans[i] = 1;
            }
        }
        else {
            if (three[i] == 0) {
                ans[i] = 0;
            }
            else if (three[i] == 1) {
                ans[i] = 1;
            }
            else {
                ans[i] = 0;
            }
        }
        pre = (ans[i] + three[i] + pre) / 3;
    }
    if (flag) {
        printf("0\n");
        return 0;
    }
    else {
        long long m = 0;
        for (int i = cnt - 1; i >= 0; i--) {
            m = (m * 3) + ans[i];
        }
        if (m == 0) {
            m = 1;
            for (int i = 0; i < cnt; i++) {
                m *= 3;
            }
        }
        cout << m + n << " " << m << endl;
    }
    return 0;
}
