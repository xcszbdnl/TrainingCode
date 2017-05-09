#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int dp[1007];
    vector<int> path[1007];
    vector<string> dfs(int point, string cnt_s) {
        vector<string> cnt_result;
        if (point == 0) {
            string cnt_s = "";
            cnt_result.push_back(cnt_s);
            return cnt_result;
        }
        for (int i = 0; i < path[point].size(); i++) {
            int next_p = path[point][i];
            vector<string> pre = dfs(next_p, cnt_s);
            string cnt_word = "";
            for (int j = next_p; j < point; j++) {
                cnt_word += cnt_s[j];
            }
            for (int j = 0; j < pre.size(); j++) {
                string pre_s = pre[j];
                if (pre[j].size() == 0) {
                    pre_s += cnt_word;
                }
                else {
                    pre_s += " " + cnt_word;
                }
                cnt_result.push_back(pre_s);
            }
        }
        return cnt_result;
    }

    vector<string> wordBreak(string s, vector<string>& wordDict) {
        memset(dp, 0, sizeof(dp));
        map<string, int> maps;
        vector<string> result;
        for (int i = 0; i < wordDict.size(); i++) {
            string cnt_s = wordDict[i];
            if (!maps.count(cnt_s)) {
                maps[cnt_s] = 1;
            }
        }
        dp[0] = 1;
        int tot_len = s.size();
        for (int i = 1; i <= tot_len; i++) {
            for (int j = i - 1; j >= 0; j--) {
                string cnt_s = "";
                for (int k = j; k < i; k++) {
                    cnt_s += s[k];
                }
                if (maps.count(cnt_s) && dp[j] == 1) {
                    dp[i] = 1;
                    path[i].push_back(j);
                }
            }
        }
        return dfs(tot_len, s);
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    string s = "catsanddog";
    vector<string> w;
    string s1 = "cat";
    w.push_back(s1);
    s1 = "cats";
    w.push_back(s1);
    s1 = "and";
    w.push_back(s1);
    s1 = "sand";
    w.push_back(s1);
    s1 = "dog";
    w.push_back(s1);
    Solution a;
    vector<string> result = a.wordBreak(s, w);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }
    return 0;
}
