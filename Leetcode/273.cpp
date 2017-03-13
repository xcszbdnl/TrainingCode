#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    string english[10] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    string ten_twenty[10] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    string ten_pow[10] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    string english_pow[5] = {"", "Thousand", "Million", "Billion"};
    string numberToWords(int num) {
        int nums[4][3] = {0};
        int pow = 10 * 10 * 10;
        int idx = 0;
        while (num) {
            int cnt_num = num % pow;
            for (int j = 0; j < 3; j++) {
                nums[idx][j] = cnt_num % 10;
                cnt_num /= 10;
            }
            idx++;
            num /= pow;
        }
        string result = "";
        for (int i = 3; i >= 0; i--) {
            int flag = 0;
            if (nums[i][2] != 0) {
                result += english[nums[i][2]] + " Hundred ";
                //cout << english[nums[i][2]] << " Hundred ";
                flag = 1;
            }
            int ten_flag = 0;
            if (nums[i][1] > 0) {
                if (nums[i][1] == 1) {
                    result += ten_twenty[nums[i][0]] + " ";
                    //cout << ten_twenty[nums[i][0]] << " ";
                    ten_flag = 1;
                }
                else {
                    result += ten_pow[nums[i][1]] + " ";
                    //cout << ten_pow[nums[i][1]] << " ";
                }
                flag = 1;
            }
            if (!ten_flag && (nums[i][0] > 0)) {
                result += english[nums[i][0]] + " ";
//                cout << english[nums[i][0]] << " ";
                flag = 1;
            }
            if (flag == 1) {
                result += english_pow[i] + " ";
//                cout << english_pow[i] << " ";
            }
        }
        int trim_space = result.size();
        for (int i = result.size() - 1; i--; i >= 0) {
            if (result[i] != ' ') {
                trim_space = i + 1;
                break;
            }
        }
        string final_result = "";
        for (int i = 0; i < trim_space; i++) {
            final_result += result[i];
        }
        if (final_result.size() == 0) {
            final_result = "Zero";
        }
        return final_result;
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    string english[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    int k;
    scanf("%d", &k);
    Solution a;
    cout << a.numberToWords(k);

}
