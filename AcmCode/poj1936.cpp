/**
 *FILENAME: poj1936.cpp
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
/**
 *DISCRIPTION:
 *To find a string is or isn't the subsequence of another
 *string,just cout that,if the counter equals the lenth of
 *the string,output yes.Otherwise,no
 */

int main() {
    while (cin >> s >> t) {
        int lenth_s = strlen(s);
        int lenth_t = strlen(t);
        int counter = 0;
        for(int i = 0; i <= lenth_t; i++) {
            if (counter == lenth_s) {
                break;
            }
            if (s[counter] == t[i]) {
                counter++;
            }
        }
        if (counter == lenth_s) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No"  << endl;
        }
    }
    return 0;
}
