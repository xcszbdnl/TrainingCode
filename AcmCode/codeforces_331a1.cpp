#include <cstdio>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

vector<int> temp, ans;
const int MAX_NUMBER = 106;
const long long INF = 100000000000000ll;
long long sums;

long long value[MAX_NUMBER];
int number;

int main() {
    freopen("input.txt", "r", stdin);
    sums = -INF;
    scanf("%d", &number);
    for (int i = 1; i <= number; i++) {
        cin >> value[i];
    }
    for (int i = 1; i <= number; i++) {
        for (int j = i + 1; j <= number; j++) {
            if (value[i] == value[j]) {
                long long temp_sums = 2 * value[i];
                temp.clear();
                for (int k = 1; k < i; k++) {
                    temp.push_back(k);
                }
                for (int k = j + 1; k <= number; k++) {
                    temp.push_back(k);
                }
                for (int k = i + 1; k < j; k++) {
                    if (value[k] < 0) {
                        temp.push_back(k);
                    }
                    else {
                        temp_sums += value[k];
                    }
                }
                if (temp_sums > sums) {
                    sums = temp_sums;
                    ans.clear();
                    for (int i = 0; i < temp.size(); i++) {
                        ans.push_back(temp[i]);
                    }
                }
            }
        }
    }
    cout << sums << " " << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        if (!i) {
            cout << ans[i];
        }
        else {
            cout << " " << ans[i];
        }
    }
    cout << endl;
    return 0;
}
