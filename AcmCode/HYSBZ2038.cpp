#include <cstdio>
#include <cstring>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
const int maxn = 100007;

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
struct Query {
    int l, r, order;
    int c;

    bool operator < (const struct Query &a) const {
        if (c == a.c) {
            return r < a.r;
        }
        return c < a.c;
    }
};

struct Ans {
    long long a, b;
};
map<int, long long> maps;
map<int, long long>::iterator it;
struct Query q[maxn];
struct Ans ans[maxn], temp_ans[maxn];
int n, q_num, val[maxn];



void getAns(int i, long long n1, long long n2) {
    if (n2 == 0) {
        n2 = 1;
        n1 = 0;
    }
    long long com = gcd(n1, n2);
    n1 /= com;
    n2 /= com;
    ans[i].a = n1;
    ans[i].b = n2;
}

int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &q_num) != EOF) {
        maps.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
        }
        for (int i = 1; i <= q_num; i++) {
            scanf("%d%d", &q[i].l, &q[i].r);
            q[i].c = q[i].l / sqrt(n + eps) + 0.5;
            q[i].order = i;
        }
        sort(q + 1, q + 1 + q_num);
        long long tot_sum = 0;
        long long cnt_sum = 0;
        for (int i = q[1].l; i <= q[1].r; i++) {
            if (maps.count(val[i])) {
                maps[val[i]]++;
            }
            else {
                maps[val[i]] = 1;
            }
        }
        for (it = maps.begin(); it != maps.end(); it++) {
            long long num = it->second;
            long long temp = num * (num - 1) / 2;
            cnt_sum += temp;
        }
        tot_sum = (q[1].r - q[1].l + 1);
        tot_sum = tot_sum * (tot_sum - 1) / 2;
        getAns(1, cnt_sum, tot_sum);
        for (int i = 2; i <= q_num; i++) {
            if (q[i].l < q[i - 1].l) {
                for (int j = q[i].l; j < q[i - 1].l; j++) {
                    if (maps.count(val[j])) {
                        maps[val[j]]++;
                    }
                    else {
                        maps[val[j]] = 1;
                    }
                }
            }
            else {
                for (int j = q[i - 1].l; j < q[i].l; j++) {
                    maps[val[j]]--;
                    if (maps[val[j]] == 0) {
                        maps.erase(val[j]);
                    }
                }
            }
            if (q[i].r < q[i - 1].r) {
                for (int j = q[i - 1].r; j > q[i].r; j--) {
                    maps[val[j]]--;
                    if (maps[val[j]] == 0) {
                        maps.erase(val[j]);
                    }
                }
            }
            else {
                for (int j = q[i - 1].r + 1; j <= q[i].r; j++) {
                    if (maps.count(val[j])) {
                        maps[val[j]]++;
                    }
                    else {
                        maps[val[j]] = 1;
                    }
                }
            }
            long long tot_sum = 0;
            long long cnt_sum = 0;
            for (it = maps.begin(); it != maps.end(); it++) {
                long long num = it->second;
                long long temp = num * (num - 1) / 2;
                cnt_sum += temp;
            }
            tot_sum = (q[i].r - q[i].l + 1);
            tot_sum = tot_sum * (tot_sum - 1) / 2;
            getAns(i, cnt_sum, tot_sum);
        }
        for (int i = 1; i <= q_num; i++) {
            temp_ans[q[i].order] = ans[i];
        }
        for (int i = 1; i <= q_num; i++) {
            printf("%I64d/%I64d\n", temp_ans[i].a, temp_ans[i].b);
        }
    }
    return 0;
}
