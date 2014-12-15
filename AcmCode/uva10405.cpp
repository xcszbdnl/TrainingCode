#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
using namespace std;
const int MAX_NUMBER = 1200;
char str1[MAX_NUMBER];
char str2[MAX_NUMBER];
int LCS[MAX_NUMBER][MAX_NUMBER];
int strlen_1, strlen_2;

void solve() {
    for (int i = 0; i <= strlen_1; i++) {
        LCS[i][0] = 0;
    }
    for (int i = 0; i <= strlen_2; i++) {
        LCS[0][i] = 0;
    }
    for (int i = 1; i <= strlen_1; i++) {
        for (int j = 1; j<= strlen_2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                LCS[i][j] = LCS[i- 1][j - 1] + 1;
            }
            else {
                if (LCS[i][j - 1] > LCS[i - 1][j]) {
                    LCS[i][j] = LCS[i][j - 1];
                }
                else {
                    LCS[i][j] = LCS[i - 1][j];
                }
            }
        }
    }
}
int main() {
    freopen("input.txt","r",stdin);
    while (gets(str1)) {
        gets(str2);
        memset(LCS,0,sizeof(LCS));
        strlen_1 = strlen(str1);
        strlen_2 = strlen(str2);
        solve();
        cout << LCS[strlen_1][strlen_2] << endl;
    }
    return 0;
}
