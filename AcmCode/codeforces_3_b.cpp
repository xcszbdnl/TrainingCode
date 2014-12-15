#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 100007;
struct Ob {
    int val, order;
};
vector<int> ans;
struct Ob kaya[maxn], cata[maxn];
int nkaya, ncata, n;
int v;

bool cmp(struct Ob a, struct Ob b) {
    return a.val < b.val;
}
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &v);
    nkaya = ncata = 0;
    memset(cata, 0, sizeof(cata));
    memset(kaya, 0, sizeof(kaya));
    ans.clear();
    for (int i = 1; i <= n; i++) {
        int type, value;
        scanf("%d%d", &type, &value);
        if (type == 1) {
            kaya[++nkaya].val = value;
            kaya[nkaya].order = i;
        }
        else {
            cata[++ncata].val = value;
            cata[ncata].order = i;
        }
    }
    sort(kaya + 1, kaya + 1 + nkaya, cmp);
    sort(cata + 1, cata + 1 + ncata, cmp);
    int result = 0;
    if (v % 2 == 1 && nkaya >= 1) {
        result += kaya[nkaya].val;
        ans.push_back(kaya[nkaya].order);
        nkaya--;
        v--;
    }
    while (nkaya >= 1 || ncata >= 1) {
        if (v == 0) {
            break;
        }
        if (v == 1) {
            if (nkaya >= 1) {
                result += kaya[nkaya].val;
                ans.push_back(kaya[nkaya].order);
            }
            break;
        }
        if (ncata >= 1) {
            if (nkaya >= 2) {
                if (kaya[nkaya].val + kaya[nkaya - 1].val > cata[ncata].val) {
                    result += kaya[nkaya].val + kaya[nkaya - 1].val;
                    ans.push_back(kaya[nkaya].order);
                    ans.push_back(kaya[nkaya - 1].order);
                    nkaya -= 2;
                    v -= 2;
                }
                else {
                    result += cata[ncata].val;
                    ans.push_back(cata[ncata].order);
                    ncata--;
                    v -= 2;
                }
            }
            else if (nkaya == 1) {
                if (kaya[1].val > cata[ncata].val) {
                    result += kaya[1].val;
                    ans.push_back(kaya[1].order);
                    nkaya = 0;
                    v -= 1;
                }
                else {
                    result += cata[ncata].val;
                    ans.push_back(cata[ncata].order);
                    ncata--;
                    v -= 2;
                }
            }
            else {
                result += cata[ncata].val;
                ans.push_back(cata[ncata].order);
                ncata--;
                v -= 2;
            }
        }
        else {
            result += kaya[nkaya].val;
            ans.push_back(kaya[nkaya].order);
            v -= 1;
            nkaya--;
        }
    }
    printf("%d\n", result);
    for (int i = 0; i < ans.size(); i++) {
        if (i == 0) {
            printf("%d", ans[0]);
        }
        else {
            printf(" %d", ans[i]);
        }
    }
    printf("\n");
    return 0;
}
