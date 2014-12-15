#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;
const int MAX_NUMBER = 25;
int LCS[MAX_NUMBER][MAX_NUMBER];
int correct_order[MAX_NUMBER];
int student_order[MAX_NUMBER];
int event_number;
void solve() {
    for (int i = 0; i <= event_number; i++) {
        LCS[i][0] = 0;
        LCS[0][i] = 0;
    }
    for (int i = 1; i <= event_number; i++) {
        for (int j = 1; j <= event_number; j++) {
            if (correct_order[i] == student_order[j]) {
                LCS[i][j] = LCS[i - 1][j - 1] + 1;
            }
            else {
                if (LCS[i - 1][j] > LCS[i][j - 1]) {
                    LCS[i][j] = LCS[i - 1][j];
                }
                else {
                    LCS[i][j] = LCS[i][j - 1];
                }
            }
        }
    }
}

int main() {
    freopen("input.txt","r",stdin);
    cin >> event_number;
    int temp;
    for (int i = 1; i <= event_number; i++) {
        cin >> temp;
        correct_order[temp] = i;
    }
    
    while (cin >> temp ) {
        student_order[temp] = 1;
        for (int i = 2; i <= event_number; i++) {
            cin >> temp;
            student_order[temp] = i;
        }
        memset(LCS,0,sizeof(LCS));
        solve();
        cout << LCS[event_number][event_number] << endl;
    }
    return 0;
}
      
