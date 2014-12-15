#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
const int maxn = 100007;
const int INF = 10000007;
long long val[maxn];
long long num[maxn];
int n;
long long ans;
int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        num[val[i]]++;
    }
    sort(val + 1, val + 1 + n);
    val[n + 1] = INF;
    int cnt_loc = 1;
    ans = 0;
    while(cnt_loc <= n) {
        int seg = cnt_loc;
        while (val[seg] == val[cnt_loc]) {
            seg++;
        }
        if (val[seg] == val[cnt_loc] + 1) {
            int two_seg = seg;
            while (val[two_seg] == val[seg]) {
                two_seg++;
            }
            if (val[two_seg] == val[seg] + 1) {
                int three_seg = two_seg;
                while (val[three_seg] == val[seg] + 1) {
                    three_seg++;
                }
                long long three_num = three_seg - two_seg;
                three_num = three_num * val[two_seg];
                long long one_num = seg - cnt_loc;
                one_num = one_num * val[cnt_loc];
                long long two_num = two_seg - seg;
                two_num = two_num * val[two_seg - 1];
                if (one_num + three_num > two_num) {
                    ans += one_num;
                    cnt_loc = two_seg;
                }
                else {
                    ans += two_num;
                    cnt_loc = three_seg;
                }
            }
            else {
                long long one_num = seg - cnt_loc;
                long long two_num = two_seg - seg;
                one_num = one_num * val[cnt_loc];
                two_num = two_num * val[two_seg - 1];
                if (one_num > two_num) {
                    ans += one_num;
                }
                else {
                    ans += two_num;
                }
                cnt_loc = two_seg;
            }
        }
        else {
            ans += (seg - cnt_loc) * val[cnt_loc];
            cnt_loc = seg;
        }
    }
    cout << ans << endl;
    return 0;
}
