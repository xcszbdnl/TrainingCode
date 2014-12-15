#include <cstdio>
#include <cstring>

const int maxn = 100007;

int time[maxn];
int pre_sum[maxn], suf_sum[maxn];
int n;

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &time[i]);
    }
    int loc_1, loc_2;
    loc_1 = 0, loc_2 = n + 1;
    int time_1, time_2;
    time_1 = time_2 = 0;
    int ans_1, ans_2;
    ans_1 = ans_2 = 0;
    while (loc_1 < loc_2 - 1) {
        if (time_1 == time_2) {
            if (loc_1 + 2 == loc_2) {
                ans_1++;
                break;
            }
            else {
                loc_1++;
                loc_2--;
                ans_1++;
                ans_2++;
                time_1 += time[loc_1];
                time_2 += time[loc_2];
            }
        }
        else if (time_1 < time_2) {
            loc_1++;
            ans_1++;
            time_1 += time[loc_1];
        }
        else {
            loc_2--;
            ans_2++;
            time_2 += time[loc_2];
        }
    }
    printf("%d %d\n", ans_1, ans_2);
}
