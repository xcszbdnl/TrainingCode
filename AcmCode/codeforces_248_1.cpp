#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 100007;

vector<int> loc[maxn];
long long val[maxn], n, m, temp[maxn];
long long result;

long long myabs(long long a) {
    return a > 0 ? a : -a;
}
int main() {
//    freopen("input.txt", "r", stdin);

    cin >> n >> m;
    result = 0;
    long long ans = -1;
    for (int i = 1; i <= m; i++) {
        cin >> val[i];
        loc[val[i]].push_back(i);
        if (i >= 2) {
            result = result + myabs(val[i] - val[i - 1]);
        }
    }
    if (m == 1) {
        cout << "0" << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        if (loc[i].size() == 0) {
            continue;
        }
//        memset(vis, 0, sizeof(vis));
//        memset(vis, 0, sizeof(vis));
        int num = 1;
        long long cnt_temp = result;
        for (int j = 0; j < loc[i].size(); j++) {
            int cnt_loc = loc[i][j];
            if (cnt_loc == 1 && val[1] != val[2]) {
                temp[num++] = val[2];
                cnt_temp -= myabs(val[2] - val[1]);
            }
            if (cnt_loc == m && val[m] != val[m - 1]) {
                if (val[m - 1] != val[m]) {
                    cnt_temp -= myabs(val[m] - val[m - 1]);
                    temp[num++] = val[m - 1];
                }
            }
            if (cnt_loc >= 2 && cnt_loc <= m - 1) {
                if (val[cnt_loc + 1] != val[cnt_loc]) {
                    cnt_temp -= myabs(val[cnt_loc + 1] - val[cnt_loc]);
                    temp[num++] = val[cnt_loc + 1];
                }
                if (val[cnt_loc - 1] != val[cnt_loc]) {
                    cnt_temp -= myabs(val[cnt_loc] - val[cnt_loc - 1]);
                    temp[num++] = val[cnt_loc - 1];
                }
            }
        }
        sort(temp + 1, temp + num);
        num--;
        long long cnt_number = temp[(num + 1) / 2];
//        memset(vis, 0, sizeof(vis));
        for (int j = 0; j < loc[i].size(); j++) {
            int cnt_loc = loc[i][j];
            if (cnt_loc == 1 && val[1] != val[2]) {
                cnt_temp += myabs(val[2] - cnt_number);
            }
            if (cnt_loc == m && val[m] != val[m - 1]) {
                cnt_temp += myabs(cnt_number - val[m - 1]);
            }
            if (cnt_loc >= 2 && cnt_loc <= m - 1) {
                if (val[cnt_loc + 1] != val[cnt_loc]) {
                    cnt_temp += myabs(val[cnt_loc + 1] - cnt_number);
                }
                if (val[cnt_loc - 1] != val[cnt_loc]) {
                    cnt_temp += myabs(cnt_number - val[cnt_loc - 1]);
                }
            }

        }
        if (ans == -1 || cnt_temp < ans) {
            ans = cnt_temp;
        }
    }
    cout << ans << endl;
}
