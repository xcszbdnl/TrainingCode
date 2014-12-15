#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <string>
#include <vector>

const int maxn = 100007;
const long long mod = 1e9 + 7;
using namespace std;
char num[maxn];
long long val[20], cnt_pow[20];
int q;
vector<string> change;

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%s", num);
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        string str;
        cin >> str;
        change.push_back(str);
    }
    for (int i = 0; i <= 10; i++) {
        val[i] = i;
        cnt_pow[i] = 10;
    }
    for (int i = q - 1; i >= 0; i--) {
        string cnt_str = change[i];
//        cout << cnt_str << endl;
        long long temp_pow = 1;
        long long cnt_value = 0;
        if (cnt_str.size() > 3) {
            for (int j = 3; j < cnt_str.size(); j++) {
                int cnt_num = cnt_str[j] - '0';
//                printf("num:%d\n", cnt_num);
                cnt_value = ((cnt_value * cnt_pow[cnt_num]) % mod + val[cnt_num]) % mod;
                temp_pow = (temp_pow * cnt_pow[cnt_num]) % mod;
            }
        }
        val[cnt_str[0] - '0'] = cnt_value;
        cnt_pow[cnt_str[0] - '0'] = temp_pow;
//        printf("val:%d-->%I64d\n", cnt_str[0] - '0', val[cnt_str[0] - '0']);
//        printf("pow:%d-->%I64d\n", cnt_str[0] - '0', cnt_pow[cnt_str[0] - '0']);
    }
    int len = strlen(num);
    long long cnt_value = 0;
    long long temp_pow = 1;
    for (int i = 0; i < len; i++) {
        int cnt_num = num[i] - '0';
        cnt_value = ((cnt_value * cnt_pow[cnt_num]) % mod + val[cnt_num]) % mod;
        temp_pow = (temp_pow * cnt_pow[cnt_num]) % mod;
    }
    printf("%I64d\n", cnt_value);
    return 0;
}
