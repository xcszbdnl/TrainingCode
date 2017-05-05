#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int max_sum;
    int getMaxPath(TreeNode *root) {
        if (root->left == NULL && root->right == NULL) {
            if (max_sum < root->val) {
                max_sum = root->val;
            }
            return root->val;
        }
        int left_num = 0;
        if (root->left != NULL) {
            left_num = getMaxPath(root->left);
            if (left_num < 0) {
                left_num = 0;
            }
        }
        int right_num = 0;
        if (root->right != NULL) {
            right_num = getMaxPath(root->right);
            if (right_num < 0) {
                right_num = 0;
            }
        }
        if (left_num + right_num + root->val > max_sum) {
            max_sum = left_num + right_num + root->val;
        }
        return left_num > right_num ? left_num + root->val: right_num + root->val;
    }
    int maxPathSum(TreeNode* root) {
        max_sum = -1e10;
        getMaxPath(root);
        return max_sum;
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    Solution a;
    return 0;
}
