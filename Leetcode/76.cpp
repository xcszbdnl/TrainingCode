#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int start = 0;
        int counter = t.size();
        map<int, int> maps;
        int result_s = 0, result_e = -1, result_l = s.size() + 1;
        for (int i = 0; i < t.size(); i++) {
            if (maps.count(t[i])) {
                maps[t[i]]++;
            }
            else {
                maps[t[i]] = 1;
            }
        }
        for (int i = 0; i < s.size(); i++) {
            if (maps.count(s[i])) {
                maps[s[i]]--;
                if (maps[s[i]] >= 0) {
                    counter--;
                }
            }
            while (counter == 0) {
//                printf("fuck\n");
                if (result_l > i - start + 1) {
                    result_l = i - start + 1;
                    result_s = start;
                    result_e = i;
                }
                if (maps.count(s[start])) {
                    maps[s[start]]++;
                    if (maps[s[start]] > 0) {
                        counter++;
                    }
                }
                start++;
            }
        }
        string result = "";
        for (int i = result_s; i <= result_e; i++) {
            result += s[i];
        }
        return result;
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    Solution a;
    cout << a.minWindow("ADOBECODEBANC", "ABC") << endl;
    return 0;
}
