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
    int check(string str) {
        for (int i = 0, j = str.size() - 1; i < j; i++, j--) {
            if (str[i] != str[j]) {
                return 0;
            }
        }
        return 1;
    }
    vector<vector<int> > palindromePairs(vector<string>& words) {
        vector<vector< int> > ans;
        map<string, int> dict;
        map<pair<int, int>, int> dict_ans;
        for (int i = 0; i < words.size(); i++) {
            string cnt_key = words[i];
            reverse(cnt_key.begin(), cnt_key.end());
            dict[cnt_key] = i;
        }
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j <= words[i].size(); j++) {
                string left = words[i].substr(0, j);
                string right = words[i].substr(j);
//                cout << left << "  " << right << endl;
                if (dict.count(left) && check(right) && dict[left] != i && dict_ans.count(make_pair(i, dict[left])) == 0) {
                    ans.push_back({i, dict[left]});
                    dict_ans[make_pair(i, dict[left])] = 1;
                }
                if (dict.count(right) && check(left) && dict[right] != i && dict_ans.count(make_pair(dict[right], i)) == 0) {
                    ans.push_back({dict[right], i});
                    dict_ans[make_pair(dict[right], i)] = 1;
                }
            }
        }
        return ans;
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    vector<string> words;
    words.push_back("ab");
    words.push_back("ba");
    Solution a;
    a.palindromePairs(words);
    return 0;
}
