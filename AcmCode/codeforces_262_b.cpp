#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
long long a, b, c;
int n;
vector<long long> ans;
const int bigest = 1000 * 1000 * 1000;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%I64d%I64d%I64d", &a, &b, &c);
    long long max_num = 100000;
    long long cnt = 1;
    while (cnt <= max_num) {
        long long pre = cnt;
        long long s = cnt;
        for (int i = 1; i <= a - 1; i++) {
            s = s * pre;
        }
        s = s * b;
        s += c;
        long long temp = s;
        long long s_x = 0;
        while (temp) {
            s_x += temp % 10;
            temp /= 10;
        }
        if (s_x == cnt && s <= bigest) {
            ans.push_back(s);
        }
        cnt++;
    }
    printf("%d\n", ans.size());
    if (ans.size()) {
        for (int i = 0; i < ans.size(); i++) {
        printf("%I64d ", ans[i]);
        }
        printf("\n");
    }
    return 0;
}
