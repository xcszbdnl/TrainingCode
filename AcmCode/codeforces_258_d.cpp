#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
const int maxn = 1000007;

char input[maxn];
long long  odd[2], even[2], odd_ans, even_ans;
long long  ans[2];
int main() {
//    freopen("in.txt", "r", stdin);
//    string in;
//    cin >> in;
    scanf("%s", input);
    memset(odd, 0, sizeof(odd));
    memset(even, 0, sizeof(even));
    odd_ans = even_ans = 0;
    for (int i = 0; i < strlen(input); i++) {
        int cnt = input[i] - 'a';
        odd_ans++;
        if (i % 2 == 0) {
            odd_ans += even[cnt];
            even_ans += odd[cnt];
            even[cnt]++;
        }
        else {
            odd_ans += odd[cnt];
            even_ans += even[cnt];
            odd[cnt]++;
        }
    }
    printf("%I64d %I64d\n", even_ans, odd_ans);
    return 0;
}
