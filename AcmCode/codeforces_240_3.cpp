#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;
const int maxn = 3000007;

long long val[maxn];
long long reverse_1[50], reverse_2[50];
long long ans;
int n, q;
vector<long long> v;


void myswap(long long &a, long long &b) {
    long long temp = a;
    a = b;
    b = temp;
}

void merge_sort(long long left, long long right, int depth, vector<long long> &tofill) {
    if (left == right) {
        reverse_1[depth] = reverse_2[depth] = 0;
        tofill.push_back(val[left]);
        return ;
    }
    long long mid = (left + right) >> 1;
    vector<long long> a, b;
    merge_sort(left, mid, depth + 1, a);
    merge_sort(mid + 1, right, depth + 1, b);
    int i, j, i_2, j_2, mx;
    i = 0, j = 0;
    while (i < a.size() || j < b.size()) {
        i_2 = i, j_2 = j;
        mx = i < a.size() && (j == b.size() || a[i] > b[j]) ? a[i] : b[j];
        while (i_2 < a.size() && a[i_2] == mx) {
            tofill.push_back(mx);
            i_2++;
        }
        while (j_2 < b.size() && b[j_2] == mx) {
            tofill.push_back(mx);
            j_2++;
        }
        reverse_1[depth] += 1ll * (i_2 - i) * (b.size() - j_2);
        reverse_2[depth] += 1ll * (j_2 - j) * (a.size() - i_2);
        i = i_2;
        j = j_2;
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= 1 << n; i++) {
        scanf("%I64d", &val[i]);
    }
    merge_sort(1, 1 << n, 0, v);
    int m;
    scanf("%d", &m);
    while (m--) {
        scanf("%d", &q);
        int t = n;
        ans = 0;
        for (int i = n - q; i <= n; i++) {
            myswap(reverse_1[i], reverse_2[i]);
        }
        for (int i = 0; i <= n; i++) {
            ans += reverse_1[i];
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
