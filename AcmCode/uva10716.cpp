#include <iostream>
#include <cstring>
#include <string.h>
#include <stdio.h>
using namespace std;
const int MAX_NUMBER = 150;
char palindrome[MAX_NUMBER];
int vis[30];
void solve() {
    memset(vis,0,sizeof(vis));
    for(int i = 0; palindrome[i]; i++) {
        vis[palindrome[i] - 'a']++;
    }
    int number = 0;
    for(int i = 0; i < 30; i++) {
        if((vis[i] % 2) != 0) {
            number++;
        }
    }
    if(number > 1) {
        cout << "Impossible" << endl;
        return ;
    }
    int lenth = strlen(palindrome);
    int ans = 0;
    for(int i = 0; i < lenth / 2; i++) {
        int j = lenth - 1 - i;
        if(palindrome[i] != palindrome[j]) {
            int k,m;
            for(k = i + 1; palindrome[k] != palindrome[j]; k++)
                ;
            for(m = j - 1; palindrome[m] != palindrome[i]; m--)
                ;
            if(j - m < k - i) {
                ans += j - m;
                for(int p = m; p < k; p++) {
                    char temp = palindrome[p];
                    palindrome[p] = palindrome[p + 1];
                    palindrome[p + 1] = temp;
                }
            }
            else {
                ans += k - i;
                for(int p = k; p > i; p--) {
                    char temp = palindrome[p];
                    palindrome[p] = palindrome[p - 1];
                    palindrome[p - 1] = temp;
                }
            }
        }
    }
    cout << ans << endl;
}
                    
int main() {
    freopen("input.txt","r",stdin);
    int test_case;
    cin >> test_case;
    while(test_case--) {
        cin >> palindrome;
        solve();
    }
    return 0;
}
