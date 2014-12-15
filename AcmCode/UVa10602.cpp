#include <iostream>
#include <cstring>
//#include <stdio.h>
using namespace std;
const int MAX_WORDS = 105;
int vis[MAX_WORDS];
char words[MAX_WORDS][MAX_WORDS];
char print_words[MAX_WORDS];
int main() {
    //freopen("input.txt","r",stdin);
    int test_case;
    cin >> test_case;
    while (test_case--) {
        int words_number;
        cin >> words_number;
        for (int i = 0; i < words_number; i++) {
            cin >> words[i];
        }
        int pressed_number = 0;
        pressed_number += strlen(words[0]);
        print_words[0] = 0;
        memset(vis,0,sizeof(vis));
        int current_word_num = 0;
        for (int i = 1; i < words_number; i++) {
            vis[current_word_num] = 1;
            int max_preffix_number = 0;
            int max_preffix_pointer;
            for (int j = 0; j < words_number; j++) {
                if (!vis[j]) {
                    int k;
                    for (k = 0;words[current_word_num][k] && words[j][k] && words[current_word_num][k] == words[j][k];k++)
                        ;
                    if (k >= max_preffix_number) {
                        max_preffix_number = k;
                        max_preffix_pointer = j;
                    }
                }
            }
            pressed_number += strlen(words[max_preffix_pointer]) - max_preffix_number;
            print_words[i] = max_preffix_pointer;
            current_word_num = max_preffix_pointer;
        }
        cout << pressed_number << endl;
        for (int i = 0; i < words_number; i++) {
            cout << words[print_words[i]] << endl;
        }
    }
    return 0;
}
            
