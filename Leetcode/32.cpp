#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> parenth;
        int max_len = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                parenth.push(i);
            }
            else {
                if (!parenth.empty() && s[parenth.top()] == '(') {
                    parenth.pop();
                    int last_pos = -1;
                    if (!parenth.empty()) {
                        last_pos = parenth.top();
                    }
                    max_len = i - last_pos > max_len ? i - last_pos: max_len;
                }
                else {
                    parenth.push(i);
                }
            }
        }
        return max_len;
    }
};

int main() {
    Solution a;
    int r = a.longestValidParentheses("(()())");
    printf("%d\n", r);
    return 0;
}
