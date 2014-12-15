/**
 *FILENAME: poj2406.c
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2012-12-27
 */
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAX_LENTH = 1000020;
char str[MAX_LENTH];
int next[MAX_LENTH];
void compute_preffix() {
    
    next[0] = -1;
    int k = -1;
    for (int i = 1; str[i]; i++) {
        
        while (k > -1 && str[k + 1] != str[i]) {
            k = next[k];
        }
        
        if (str[k + 1] == str[i]) {
            k++;
        }
        
        next[i] = k;
    }
}

int main() {
    
    freopen("input.txt","r",stdin);
    
    while (1) {
        scanf("%s",str);
        
        if (memcmp(str,".",sizeof(".")) == 0) {
            break;
        }
        
        compute_preffix();
        
        int lenth = strlen(str);
        int one_string_lenth = lenth - 1  - next[lenth - 1];
        int period = 1;
        if (lenth % one_string_lenth == 0) {
            period = lenth / one_string_lenth;
        }

        cout << period << endl;
    }
    return 0;
        
}
