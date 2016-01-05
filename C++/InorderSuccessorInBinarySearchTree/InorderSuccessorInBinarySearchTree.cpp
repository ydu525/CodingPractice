/*
* see http://www.lintcode.com/en/problem/inorder-successor-in-binary-search-tree/ for problem description
*/
#include <vector>
#include <iostream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}	
};

class Solution {
public:
	TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
		// write your code here
		if (!root) {
			return last;
		}
		if (p->val == root->val) {
			if (root->right) {
				last = root;
				return inorderSuccessor(root->right, p);
			}
			return last;
		}
		else if (p->val < root->val) {
			last = root;
			return inorderSuccessor(root->left, p);
		}
		else {
			return inorderSuccessor(root->right, p);
		}
	}

private:
	TreeNode* last = NULL;

};

int main() {
	Solution s;

	TreeNode n1(1);
	TreeNode n2(2);
	TreeNode n3(3);
	TreeNode n4(4);

	n4.left = &n1;
	n1.right = &n3;
	n3.left = &n2;

	s.inorderSuccessor(&n4, &n1);

	return 0;
}