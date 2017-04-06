#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        reverse(s.begin(), s.end());
        string result = s;
        int len = s.size();
        int idx = len - 2, min_len = len;
        int flag = 0;
        for (int j = len / 2 - 1; j < len && !flag; j++) {
            int start, dest;
            for (start = j, dest = j; start >= 0 && dest < len; start--, dest++) {
                if (s[start] != s[dest]) {
                    break;
                }
            }
            if (dest == len) {
                if (start + 1 < min_len) {
                    min_len = start + 1;
                    idx = start;
                    flag = 1;
                }
            }
            for (start = j - 1, dest = j; start >= 0 && dest < len; start--, dest++) {
                if (s[start] != s[dest]) {
                    break;
                }
            }
            if (dest == len) {
                if (start + 1 < min_len) {
                    min_len = start + 1;
                    idx = start;
                    flag = 1;
                }
            }
        }
//        printf("%d\n", idx);
        for (int i = idx; i >= 0; i--) {
            result.push_back(s[i]);
        }
        return result;
    }
};

int main() {
    Solution a;
    cout << a.shortestPalindrome("aacecaaa") << endl;
    return 0;
}
