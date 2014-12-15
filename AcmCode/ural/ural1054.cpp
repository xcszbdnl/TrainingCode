#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int maxn = 50;

int state[maxn];
unsigned int f[maxn];
int main() {
//    freopen("input.txt", "r", stdin);
    f[0] = 0;
    f[1] = 1;
    int n;
    for (int i = 2; i <= 31; i++) {
        f[i] = 2 * f[i - 1] + 1;
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &state[i]);
    }
    int from, to, temp;
    from = 1;
    to = 2;
    temp = 3;
    int flag = 0;
    unsigned int ans = 0;
    for (int i = n; i >= 1; i--) {
        if (state[i] != from && state[i] != to) {
            flag = 1;
            break;
        }
        else {
            if (state[i] == to) {
                ans += f[i - 1] + 1;
                int change = from;
                from = temp;
                temp = change;
            }
            else {
                int change = to;
                to = temp;
                temp = change;
            }
        }
    }
    if (flag) {
        cout << "-1" << endl;
    }
    else {
        cout << ans <<endl;
    }
    return 0;
}
