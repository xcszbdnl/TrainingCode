/**
 *FILENAME: poj1035.cpp
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2012-12-27
 */
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_DICTIONARY_WORDS = 10005;
const int MAX_INPUT_WORDS = 55;
const int MAX_LENTH = 20;

char dictionary_words[MAX_DICTIONARY_WORDS][MAX_LENTH];
char input_word[MAX_INPUT_WORDS];
int words_number;
int words_right[MAX_DICTIONARY_WORDS];
/**
 *DESCRIPTION:
 *spell check
 *If the string is in the dictionary, just input it
 *If one string can be replaced or delete only one character by the word in the
 *dictionary or insert only one arbitrary letter to the word.Print the word
 *For one string,we look up all in the dictionary
 */
int replaceOneLetter(int k) {
    int diff = 0;
    for (int i = 0; input_word[i]; i++) {
        if (input_word[i] != dictionary_words[k][i])
            diff++;
        if (diff > 1)
            return 0;
    }
    return 1;
}

int delOneLetter(int k) {
    int diff = 0;
    for (int i = 0, j = 0; input_word[i]; i++, j++) {
        if (input_word[i] != dictionary_words[k][j]) {
            j--;
            diff++;
        }
        if (diff > 1)
            return 0;
    }
    return 1;
}

int insertOneLetter(int k) {
    int diff = 0;
    for (int i = 0, j = 0; dictionary_words[k][j]; i++, j++) {
        if (input_word[i] != dictionary_words[k][j]) {
            i--;
            diff++;
        }
        if (diff > 1)
            return 0;
    }
    return 1;
}

void solve() {
    int flag = 0;
    int words_right_number = 0;
    for (int i = 0; i < words_number; i++) {
        int dic_word_lenth = strlen(dictionary_words[i]);
        int input_word_lenth = strlen(input_word);
        if (dic_word_lenth == input_word_lenth) {
            if (strcmp(dictionary_words[i],input_word) == 0) {
                flag = 1;
                break;
            }
            else {
                if (replaceOneLetter(i)) {
                    words_right[words_right_number++] = i;
                }
            }
        }
        else if (dic_word_lenth - input_word_lenth == 1) {
            if (insertOneLetter(i)) {
                words_right[words_right_number++] = i;
            }
        }
        else if (input_word_lenth - dic_word_lenth == 1) {
            if (delOneLetter(i)) {
                words_right[words_right_number++] = i;
            }
        }
    }
    if (flag) {
        cout << input_word << " is correct" ;
    }
    else {
        cout << input_word << ":";
        for (int i = 0; i < words_right_number; i++) {
            cout << " " << dictionary_words[words_right[i]];
        }
    }
    cout << endl;
}


            

int main() {


    while (cin >> dictionary_words[words_number] ) {
        if (dictionary_words[words_number][0] == '#')
            break;
        words_number++;
    }
    
    while (cin >> input_word) {
        if (input_word[0] == '#')
            break;
        solve();
    }
}
