/**
 *FILENAME: poj2388.cpp
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2012-12-29
 */

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_NUMBER = 10010;
int cows[MAX_NUMBER];
/**
 *DESCRIPTION:
 *Just very simple question,sort it and output the
 *(lenth / 2)th element
 */


int main() {
    freopen("input.txt","r",stdin);
    int lenth;

    cin >> lenth;

    for (int i = 0; i < lenth; i++) {
        cin >> cows[i];
    }
    sort(cows, cows + lenth);
    cout << cows[lenth / 2] << endl;

}
