/**
 *FILENAME: poj1961.cpp
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2012-12-26
 */
#include <iostream>
#include <cstdio>
using namespace std;

const int MAX_NUMBER = 1000010;
char str[MAX_NUMBER];
int next[MAX_NUMBER];
int lenth;
/**
 *DESCRIPTION:
 *use KMP to find the period
 */


void compute_preffix() {
    next[0] = -1;
    int i, j;
    i = 0;
    j = -1;
    while (i < lenth) {
        if (j == -1 || str[i] == str[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}

int main() {
    freopen("input.txt","r",stdin);

    int test_case = 1;
    while (cin >> lenth) {
        if (lenth == 0) {
            break;
        }
        scanf("%s",str);
        compute_preffix();
        if (test_case != 1) {
            cout << endl;
        }
        cout << "Test case #" << test_case << endl;
        test_case++;
        for (int i = 2; i <= lenth; i++) {
            if ((i % (i - next[i]) == 0) && (i / (i - next[i]) > 1)) {
                cout << i << " " << i / (i - next[i]) << endl;
            }
        }
    }
}
