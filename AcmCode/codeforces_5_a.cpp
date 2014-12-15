#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int maxn = 1008;

char in[maxn];

int main() {
//    freopen("in.txt", "r", stdin);
    long long ans = 0;
    int in_number = 0;
    while (gets(in)) {
        if (in[0] == '+' || in[0] == '-') {
            if (in[0] == '+') {
                in_number++;
            }
            else {
                in_number--;
            }
        }
        else {
            int tot_len = 0;
            for (int i = 0; i < strlen(in); i++) {
                if (in[i] == ':') {
                    tot_len = strlen(in) - i - 1;
                    break;
                }
            }
            ans += tot_len * in_number;
//            printf("%d:%d\n", tot_len, in_number);
        }
    }
    cout << ans << endl;
}
