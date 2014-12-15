#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;
const int MAX_NUMBER = 10000001;
long long wines[MAX_NUMBER];
long long ans;
int main() {
    freopen("input.txt","r",stdin);
    while(1) {
        ans = 0;
        int inhabitants;
        cin >> inhabitants;
        if(!inhabitants) {
            break;
        }
        for(int i = 0; i < inhabitants; i++) {
            cin >> wines[i];
        }
        for(int i = 1; i < inhabitants; i++) {
            wines[i] += wines[i - 1];
            ans += abs(wines[i - 1]);
        }
        cout << ans << endl;
    }
    return 0;
}
     
