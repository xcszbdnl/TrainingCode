#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;
const int MAX_NUMBER = 100;
int f[MAX_NUMBER];
int temp_f[MAX_NUMBER];
int d[MAX_NUMBER];
int fish_time[MAX_NUMBER];
int temp_time[MAX_NUMBER];
int ans_time[MAX_NUMBER];
int n;
int minutes;
int max_fish;
void solve() {
    for (int i = 0; i < n; i++) {
        int fish_numbers = 0;
        int temp_minutes = minutes;
        memcpy(temp_f,f,sizeof(f));
        memset(temp_time,0,sizeof(temp_time));
        for (int j = 1; j <= i; j++) {
           temp_minutes -= 5 * fish_time[j];
        }
        int k = temp_minutes / 5;
        for (int m = 1; m <= k; m++) {
            int temp_max = temp_f[0];
            int to_fish_index= 0;
            for (int k = 0; k <= i; k++) {
                if (temp_f[k] > temp_max) {
                    temp_max = temp_f[k];
                    to_fish_index = k;
                }
            }
            fish_numbers += temp_max;
            if (temp_f[to_fish_index ] > 0) {
                temp_f[to_fish_index] -= d[to_fish_index];
            }
            temp_time[to_fish_index] += 5;
        }
        if (fish_numbers > max_fish) {
            max_fish = fish_numbers;
            memcpy(ans_time,temp_time,sizeof(ans_time));
        }
    }
}
int main() {
    freopen("input.txt","r",stdin);
    cin >> n;
    while (1) {
        if (n == 0) {
            break;
        }
        memset(f,0,sizeof(f));
        memset(d,0,sizeof(d));
        cin >> minutes;
        minutes *= 60;
        for (int i = 0; i < n; i++) {
            cin >> f[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> d[i];
        }
        for (int i = 1; i < n; i++) {
            cin >> fish_time[i];
        }
        max_fish = 0;
        solve();
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                cout << ans_time[i];
            }
            else {
                cout << ", " << ans_time[i];
            }
        }
        cout << endl;
        cout << "Number of fish expected: " << max_fish << endl;
        cin >> n;
        if (n != 0) {
            cout << endl;
        }
    }
    return 0;
}
