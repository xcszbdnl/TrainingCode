#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int MAX_NUMBER = 4006;
long long sums[MAX_NUMBER];
char str[MAX_NUMBER];
int vis[MAX_NUMBER * 9];
long long ans;
int length, a;
int main() {

    memset(vis, 0, sizeof(vis));
    memset(sums, 0, sizeof(sums));
    scanf("%d", &a);
    scanf("%s", str);
    length = strlen(str);
    for (int i = 0; i < length; i++) {
        sums[i + 1] = sums[i] + str[i] - '0';
    }
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j <= length; j++) {
            int temp = sums[j] - sums[i];
            vis[temp]++;
        }
    }
    if (a == 0) {
        ans = (long long)vis[0] * length * (length + 1) - (long long)vis[0] * vis[0];
    }
    else {
        for (int i = 1; i < 9 * MAX_NUMBER; i++) {
            if (a % i == 0) {
                int other = a / i;
                if (other < 9 * MAX_NUMBER) {
                    ans = ans + (long long)vis[i] * vis[other];
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
