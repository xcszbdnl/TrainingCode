#include <cstdio>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        map<int, vector<int> > loc;
        int vis[30];
        int char_num = 0;
        string result = "";
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < s.size(); i++) {
            int cnt_char = s[i] - 'a';
            vis[cnt_char] = 1;
            if (loc.count(cnt_char)) {
                loc[cnt_char].push_back(i);
            }
            else {
                vector<int> locs;
                char_num++;
                loc[cnt_char] = locs;
                loc[cnt_char].push_back(i);
            }
        }
        int pre_loc = -1;
        while (char_num--) {
            int min_char = -1, first_loc = 0;
            for (int i = 0; i < 26; i++) {
                if (vis[i]) {
                    vector<int> loc_v = loc[i];
                    for (int j = 0; j < loc_v.size(); j++) {
                        int cnt_loc = loc_v[j];
                        if (cnt_loc > pre_loc) {
                            first_loc = cnt_loc;
                            break;
                        }
                    }
                    int flag = 0;
                    for (int j = 0; j < 26; j++) {
                        if (!vis[j]) {
                            continue;
                        }
                        int last_loc = loc[j].back();
                        if (first_loc > last_loc) {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag) {
                        vis[i] = 0;
                        result += s[first_loc];
                        pre_loc = first_loc;
                        break;
                    }
                }
            }
        }
        return result;
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    string s = "cbacdcbc";
    Solution a;
    cout << a.removeDuplicateLetters(s);
    return 0;
}
