#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
using namespace std;
const int MAX_NUMBER = 25;
char correct_order[MAX_NUMBER];
char student_order[MAX_NUMBER];
int LCS[MAX_NUMBER][MAX_NUMBER];
int event_number;
void deal_with_array(char *s) {
    char temp[MAX_NUMBER];
    char *target = s;
    int c = 0;
    int pointer = 0;
    while (*s) {
        if (*s == ' ') {
            temp[pointer++] = c + 'a';
            c = 0;
        }
        else {
            c = c * 10 + *s - '0';
        }
        s++;
    }
    temp[pointer++] = c + 'a';
    temp[pointer] = '\0';
    memcpy(target,temp,sizeof(temp));
}
void solve() {
    for (int i = 0; i <= event_number; i++) {
        LCS[i][0] = 0;
        LCS[0][i] = 0;
    }
    for (int i = 1; i <= event_number; i++) {
        for (int j = 1; j <= event_number; j++) {
            if (correct_order[i - 1] == student_order[j - 1]) {
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
    cin.get();
    cin.getline(correct_order,MAX_NUMBER);
    deal_with_array(correct_order);
    while (cin.getline(student_order,MAX_NUMBER)) {
        deal_with_array(student_order);
        memset(LCS,0,sizeof(LCS));
        solve();
        cout << LCS[event_number][event_number] << endl;
    }
    return 0;
}
   
