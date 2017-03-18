#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    int check_ok(string s, vector<string> &words, int start, int dest, map<string, int> &word_maps) {
        map<string, int> maps;
        int word_length = words[0].size();
        for (int i = start; i < dest; i += word_length) {
            string cnt_s = "";
            for (int j = i; j < i + word_length; j++) {
                cnt_s += s[j];
            }
            if (maps.count(cnt_s)) {
                maps[cnt_s] += 1;
            }
            else {
                maps[cnt_s] = 1;
            }
        }
        map<string, int>::iterator it;
        for (it = maps.begin(); it != maps.end(); it++) {
            string cnt_key = it->first;
            if (!word_maps.count(cnt_key)) {
                return 0;
            }
            else if (word_maps[cnt_key] != it->second) {
                return 0;
            }
        }
        return 1;
    }
    vector<int> findSubstring(string s, vector<string>& words) {
        map<string, int> word_maps;
        int hash_num = 0;
        const int MOD = 10007;
        int tot_len = 0;
        vector<int> results;
        if (words.size() == 0) {
            return results;
        }
        for (int i = 0; i < words.size(); i++) {
            string cnt_word = words[i];
            if (word_maps.count(cnt_word)) {
                word_maps[cnt_word] += 1;
            }
            else {
                word_maps[cnt_word] = 1;
            }
            for (int j = 0; j < cnt_word.size(); j++) {
                tot_len++;
                int cnt_num = cnt_word[j] > 'z' ? cnt_word[j] - 'A': cnt_word[j] - 'a';
                hash_num = (hash_num + cnt_num) % MOD;
            }
        }
        if (s.size() < tot_len) {
            return results;
        }
        int string_num = 0;
        for (int i = 0; i < tot_len - 1; i++) {
            int cnt_num = s[i] > 'z' ? s[i] - 'A' : s[i] - 'a';
            string_num = (string_num + cnt_num) % MOD;
        }
        int pre_num = 0;
        for (int i = 0; i < s.size(); i++) {
            int cnt_num = s[i + tot_len - 1] > 'z' ? s[i + tot_len - 1] - 'A' : s[i + tot_len - 1] - 'a';
            string_num = (string_num - pre_num + MOD) % MOD;
            string_num = (string_num + cnt_num + MOD) % MOD;
            if (string_num == hash_num) {
                if (check_ok(s, words, i, i + tot_len, word_maps)) {
                    results.push_back(i);
                }
            }
            pre_num = s[i] > 'z' ? s[i] - 'A' : s[i] - 'a';
        }
        return results;
    }
};

int main() {
    string s = "barfoothefoobarman";
    vector<string> a;
    string s1 = "foo";
    a.push_back(s1);
    s1 = "bar";
    a.push_back(s1);
    Solution k;
    vector<int> r = k.findSubstring(s, a);
    for (int i = 0; i < r.size(); i++) {
        printf("%d\n", r[i]);
    }
    return 0;
}
