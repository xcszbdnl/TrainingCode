#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 207;
const int INF = 100000007;
struct Num {
    int number;
    int order;
    bool operator < (const struct Num &a) const {
        return number > a.number;
    }
};
int val[maxn];
int temp[maxn], n, k;
struct Num num[maxn];
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    int max_ans = -INF;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
        num[i].number = val[i];
        num[i].order = i;
    }
    sort(num + 1, num + 1 + n);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int cnt_num = 0;
            int cnt_sums = 0;
            for (int k = i; k <= j; k++) {
                temp[cnt_num++] = val[k];
                cnt_sums += val[k];
            }
            sort(temp, temp + cnt_num);
            int cnt_k = k;
            int cnt_loc = 1;
            int seg_loc = 0;
            while (cnt_k && cnt_loc <= n && seg_loc < cnt_num) {
                if (temp[seg_loc] > num[cnt_loc].number) {
                    break;
                }
                if (num[cnt_loc].order < i || num[cnt_loc].order > j) {
                    cnt_sums -= temp[seg_loc];
                    cnt_sums += num[cnt_loc].number;
                    seg_loc++;
                    cnt_loc++;
                    cnt_k--;
                }
                else {
                    cnt_loc++;
                }
            }
            if (cnt_sums > max_ans) {
                max_ans = cnt_sums;
            }
        }
    }
    printf("%d\n", max_ans);
    return 0;
}
