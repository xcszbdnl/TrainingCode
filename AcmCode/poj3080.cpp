/**
 *FILENAME:poj3080.cpp
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2012-12-28
 */
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int MAX_LINE = 15;
const int MAX_LENTH = 80;

char base[MAX_LINE][MAX_LENTH];
int next[MAX_LENTH];

/**
 *DESCRIPTION:
 *Find the longest common subsequence,the sequence must be continous;
 *First we get all subsequence in one string,then use
 *kmp to check that the subsequence
 *is or is not the subsequence of other string.
 */
void getNext(char *source) {
    int i, j;
    next[0] = j = -1;
    i = 0;
    while (source[i]) {
        if (j == -1 || source[j] == source[i]) {
            i++;
            j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}

int check(char *target, char *pattern, int lenth) {
    int i = 0, j = -1;
    while (target[i]) {
        if (j == -1 || target[i] == pattern[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
        if (j == lenth) {
            return 1;
        }
    }
    return 0;
}

int main() {
    freopen("input.txt","r",stdin);
    int test_case;
    char ans[MAX_LENTH];
    
    cin >> test_case;
    
    while (test_case--) {
        memset(next,0,sizeof(next));
        ans[0] = '\0';
        int ans_lenth = 0;        
        int m_lines;
        cin >> m_lines;
        for (int i = 0; i < m_lines; i++) {
            cin >> base[i];
        }
        
        int lenth = strlen(base[0]);
        for (int i = 3; i <= lenth; i++) {
            char subsequence[MAX_LENTH];
            for (int j = 0; j <= lenth - i; j++) {
                int k;
                for (k = 0; k < i; k++) {
                    subsequence[k] = base[0][j + k];
                }
                subsequence[k] = '\0';
                getNext(subsequence);
                int m;
                for (m = 1; m < m_lines; m++) {
                    if (!check(base[m], subsequence, i))
                        break;
                }
                if (m == m_lines) {
                    if (i > ans_lenth) {
                        strcpy(ans, subsequence);
                        ans_lenth = i;
                    }
                    else if (i == ans_lenth && strcmp(ans, subsequence) > 0) {
                        strcpy(ans,subsequence);
                    }
                    
                }
            }
        }
        if (ans[0] == '\0') {
            cout << "no significant commonalities" << endl;
        }
        else {
            cout << ans << endl;
        }
    }
    return 0;
}
