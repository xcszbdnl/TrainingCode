#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1000;
const int max_num = 50007;
vector<long long> v;
long long a[10][maxn], num[max_num * 10];
int head[max_num * 10], h_next[max_num * 10];
int n, s;

bool hashInsert(int cnt_num) {
    long long x = num[cnt_num];
    int hash_num = ((x % max_num) + max_num) % max_num;
    int k = head[hash_num];
    while (k != -1) {
        if (num[k] == x) {
            return true;
        }
        k = h_next[k];
    }
    h_next[cnt_num] = head[hash_num];
    head[hash_num] = cnt_num;
    return false;
}

bool hashFind(long long x) {
    int hash_num = ((x % max_num) + max_num) % max_num;
    int k = head[hash_num];
    while (k != -1) {
        if (num[k] == x) {
            return true;
        }
        k = h_next[k];
    }
    return false;
}

int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(head, -1, sizeof(head));
        memset(h_next, -1, sizeof(h_next));
        scanf("%d", &n);
        s = 0;
        for (int i = 1; i <= 5; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%I64d", &a[i][j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n ;j++) {
                long long tmp = a[1][i] + a[2][j];
                num[++s] = tmp;
                hashInsert(s);
            }
        }
        int flag = 0;
        for (int i = 1; i <= n && !flag; i++) {
            for (int j = 1; j <= n && !flag; j++) {
                for (int k = 1; k <= n && !flag; k++) {
                    long long tmp = a[3][i] + a[4][j] + a[5][k];
                    if (hashFind(-tmp)) {
                        flag = 1;
                        break;
                    }
                }
            }
        }
        if (flag) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
    return 0;
}
