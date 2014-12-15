#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#define min(a,b) ((a) > (b)) ? (b) : (a)
using namespace std;
const long long INF = 100000000007ll;
long long l, r, k;

vector<long long> temp_ans, ans;
long long min_ans;
map<long long, int> maps;

void dfs(int cnt, int chose, long long xor_ans) {
    if (cnt == chose + 1) {
        if (xor_ans < min_ans) {
            ans.clear();
            min_ans = xor_ans;
            for (int i = 0; i < temp_ans.size(); i++) {
                ans.push_back(temp_ans[i]);
            }
        }
    }
    else {
        for (long long s = l; s <= r; s++) {
            if (!maps.count(s)) {
                maps[s] = 1;
                temp_ans.push_back(s);
                dfs(cnt + 1, chose, xor_ans ^ s);
                temp_ans.pop_back();
                maps.erase(s);
            }
        }
    }
}
int main() {
    freopen("in.txt", "r", stdin);
    scanf("%I64d%I64d%I64d\n", &l, &r, &k);
    min_ans = INF;
    int min_num = min(4, k);
    if (r - l + 1 >= 8) {
        r = l + 7;
    }
    long long temp = r;
    while (temp) {
        printf("%d", temp % 2);
        temp /= 2;
    }
    for (int i = 1; i <= min_num; i++) {
        dfs(1, i, 0);
    }
    printf("%I64d\n", min_ans);
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
        printf("%I64d ", ans[i]);
    }
    printf("\n");
    return 0;
}
