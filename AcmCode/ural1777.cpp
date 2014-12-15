#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_NUMBER = 10006;


long long number[MAX_NUMBER];
long long ans;
int main() {

    cin >> number[0] >> number[1] >> number[2];
    ans = 0;
    while (1) {
        sort(number, number + 3 + ans);
        long long min_diff = -1;
        for (int i = 0; i < 2 + ans; i++) {
            long long temp = number[i + 1] - number[i];
            if (min_diff == -1 || min_diff > temp) {
                min_diff = temp;
            }
        }
        if (min_diff == 0) {
            break;
        }
        number[3 + ans] = min_diff;
        ans++;
    }
    cout << ans + 1 << endl;
    return 0;
}
