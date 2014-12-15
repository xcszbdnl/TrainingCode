#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <map>
#include <string>
using namespace std;

const int maxn = 107;
int num[maxn];
int cnt;
int n, m, price[maxn];
map<string ,int> maps;

bool cmp(int a, int b) {
    return a > b;
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }
    sort(price + 1, price + 1 + n);
    for (int i = 1; i <= m; i++) {
        string cnt_name;
        cin >> cnt_name;
        if (maps.count(cnt_name)) {
            num[maps[cnt_name]]++;
        }
        else {
            maps[cnt_name] = ++cnt;
            num[cnt] = 1;
        }
    }
    sort(num + 1, num + 1 + cnt, cmp);
    int min_ans, max_ans;
    min_ans = max_ans = 0;
    for (int i = 1; i <= cnt; i++) {
        min_ans += num[i] * price[i];
    }
    for (int i = 1; i <= cnt; i++) {
        max_ans += num[i] * price[n - i + 1];
    }
    printf("%d %d\n", min_ans, max_ans);
    return 0;
}
