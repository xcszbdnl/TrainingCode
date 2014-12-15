/**
 *FILENAME:POJ1936.cpp
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2012-12-29
 */

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_LENTH = 100010;
char s[MAX_LENTH];
char t[MAX_LENTH];
int lcs[MAX_LENTH][MAX_LENTH];

/**
 *DESCRIPTION:
 *To find that a string is or is not the subsequence of another string
 *We use dynamic methor,if f[n][m] == strlen(s), that means the string
 *is the subsequence of another string
 */
void LCS(int lenth_s, int lenth_t) {
    for (int i = 1; i <= lenth_s; i++) {
        for (int j = 1; j <= lenth_t; j++) {
            if (s[i - 1] == t[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            }
            else if (lcs[i - 1][j] > lcs[i][j - 1]) {
                lcs[i][j] = lcs[i - 1][j];
            }
            else {
                lcs[i][j] = lcs[i - 1][j];
            }
        }
    }
}

int main() {
    freopen("input.txt","r",stdin);
    while (cin >> s >> t) {
        memset(lcs, 0, sizeof(lcs));
        int lenth_s = strlen(s);
        int lenth_t = strlen(t);
        LCS(lenth_s, lenth_t);
        if (lcs[lenth_s][lenth_t] == lenth_s) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    
}
    
 
