#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
using namespace std;
const int MAX_CHAR = 110;
char palindrome[MAX_CHAR];
int main(){
    freopen("input.txt","r",stdin);
    int test_case;
    cin >> test_case;
    while(test_case--) {
        cin >> palindrome;
        int lenth = strlen(palindrome);
        int has_found = 0;
        int ans = 0;
        if(lenth % 2 == 0) {
            int flag = 0;
            int i;
            for(i = 0; i < lenth / 2 && flag != 1; i++) {
                char now_char = palindrome[i];
                int temp = lenth;
                int j;
                for(j = i + 1;j < lenth; j++) {
                    if(now_char == palindrome[j]) {
                        temp = j;
                    }
                }
                if(temp == lenth) {
                    flag = 1;
                }
                else {
                    if(temp > lenth - 1 - i) {
                        for(int k = lenth - 1 - i; k < temp; k++) {
                            char swap_char = palindrome[k];
                            palindrome[k] = palindrome[k + 1];
                            palindrome[k + 1] = swap_char;
                            ans++;
                        }
                    }
                    else {
                        for(int k = temp; k < lenth - 1 - i; k++){
                            char swap_char = palindrome[k];
                            palindrome[k] = palindrome[k + 1];
                            palindrome[k + 1] = swap_char;
                            ans++;
                        }
                    }
                }
            }
            if(i == lenth / 2)
                cout << ans  << endl;
            else
                cout << "Impossible\n";
        }
        else {
            int i;
            int flag = 0;
            for(i = 0; i < lenth / 2; i++) {
                char now_char = palindrome[i];
                int temp = lenth;
                int j;
                for(j = i+1; j < lenth && flag != 2; j++) {
                    if(now_char == palindrome[j]) {
                        temp = j;
                    }
                }
                if(temp == lenth && flag != 2) {
                    flag++;
                    for(int k = i; k < lenth / 2; k++) {
                        char swap_char = palindrome[k];
                        palindrome[k] = palindrome[k + 1];
                        palindrome[k + 1] = swap_char;
                        ans++;
                    }
                }
                else {
                    if(temp > lenth - 1 - i) {
                        for(int k = lenth - 1 -i; k < temp; k++) {
                            char swap_char = palindrome[k];
                            palindrome[k] = palindrome[k + 1];
                            palindrome[k + 1] = swap_char;
                            ans++;
                        }
                    }
                    else {
                        for(int k = temp; k < lenth - 1 - i;k++) {
                            char swap_char = palindrome[k];
                            palindrome[k] = palindrome[k + 1];
                            palindrome[k + 1] = swap_char;
                            ans++;
                        }
                    }
                }
            }
            if(i == lenth / 2) {
                cout << ans << endl;
            }
            else {
                cout << "Impossible\n";
            }
        }
    }
    return 0;
}
