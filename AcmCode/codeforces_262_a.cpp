#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
int n, m;
long long ans;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    int cnt_socks = n;
    int day = 0;
    while (cnt_socks > 0) {
        day++;
        cnt_socks--;
        if (day % m == 0) {
            cnt_socks++;
        }
    }
    printf("%d\n", day);
    return 0;
}
