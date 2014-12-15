#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_NUMBER = 10000;
int bags[MAX_NUMBER];
int bag_number;
void solve() {
    sort(bags,bags + bag_number);
    int i = 0;
    int k = 0;
    int max_number = 1;
    int lenth = 1;
    while(i < bag_number) {
        i = k;
        int now_number = bags[i];
        lenth = 1;
        for(k = i + 1; k < bag_number && now_number == bags[k]; lenth++, k++)
            ;
        if(max_number < lenth)
            max_number = lenth;
    }
    cout << max_number << endl;
    for(int i = 0; i < max_number; i++) {
        for(int m = i; m < bag_number; m += max_number) {
            if(m == i)
                cout << bags[m];
            else
                cout << " " << bags[m];
        }
        cout << endl;
    }
}

int main() {
    freopen("input.txt","r",stdin);
    while(1) {
        cin >> bag_number;
        if(bag_number == 0) {
            break;
        }
        for(int i = 0; i < bag_number; i++) {
            cin >> bags[i];
        }
        solve();
    }
    return 0;
}
