#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;
const int MAX_NUMBER = 100001;
long long wines[MAX_NUMBER];
int inhabitants;
long long ans;
void solve() {
    for(int i = 0; i < inhabitants; i++) {
        if(wines[i] < 0) {
            for(int j = i; j < inhabitants && wines[i]; j++) {
                if (wines[j] > 0) {
                    long long abs_wine_i = - wines[i];                    
                    if (abs_wine_i < wines[j]) {
                        wines[i] = 0;
                        ans += abs_wine_i * (j - i);
                        wines[j] += wines[i];
                    }
                    else {
                        ans += wines[j] * (j - i);
                        wines[i] += wines[j];
                        wines[j] = 0;
                    }
                }
            }
        }
        if (wines[i] > 0) {
            for (int j = i; j < inhabitants & wines[i]; j++) {
                if (wines[j] < 0) {
                    long long abs_wine_j = - wines[j];
                    if (abs_wine_j < wines[i]) {
                        ans += abs_wine_j * (j - i);
                        wines[i] += wines[j];
                        wines[j] = 0;
                    }
                    else {
                        ans += wines[i] * (j - i);
                        wines[j] += wines[i];
                        wines[i] = 0;
                    }
                }
            }
        }
    }
    cout << ans << endl;
}
int main() {
    freopen("input.txt","r",stdin);
    while(1) {
        cin >> inhabitants;
        if (!inhabitants) {
            break;
        }
        for (int i = 0; i< inhabitants; i++) {
            cin >> wines[i];
        }
        ans = 0;
        solve();
     }
    return 0;
}
