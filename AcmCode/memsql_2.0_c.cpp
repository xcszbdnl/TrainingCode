#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int maxn = 1000007;
using namespace std;
int num[maxn], cnt[maxn];
int n, max_person;
vector<pair<int, int> > vote;

bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.first < b.first;
}

int check(int cnt_num) {
    int h = cnt_num - num[0];
    for (int i = 1; i <= max_person; i++) {
        cnt[i] = num[i];
        h -= max(cnt[i] - cnt_num + 1, 0);
    }
    int ret = 0;
    for (int i = 0; i < vote.size(); i++) {
        int a = vote[i].first;
        int b = vote[i].second;
        if (b == 0) {
            continue;
        }
        if (cnt[b] >= cnt_num) {
            ret += a;
            cnt[b]--;
        }
        else {
            if (h > 0) {
                ret += a;
                h--;
            }
        }
    }
    return ret;
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        vote.push_back(make_pair(b, a));
        num[a]++;
        max_person = max(max_person, a);
    }
    sort(vote.begin(), vote.end());
    int low = 0;
    int high = n + 1;
    int ans = -1;
    while (low < high) {
        int mid = (low + high) >> 1;
        int midmid = (mid + high) >> 1;
        int x = check(mid);
        int y = check(midmid);
        if (ans == -1 || ans > x || ans > y) {
            ans = min(x, y);
        }
        if (x > y) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }
    printf("%d\n", ans);
    return 0;
}
