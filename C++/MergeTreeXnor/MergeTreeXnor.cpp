struct node {
	bool is_one;
	node* left;
	node* right;
	node(bool b) : is_one(b), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	node* MergeTreeXnor(node* root1, node* root2) {
		if (root1 == nullptr) {
			return root2;
		}
		else if (root2 == nullptr) {
			return root1;
		}
		
		//we should ask inteviewer whether the merged tree is still needed.
		//if not, we should implement function to delete the merged tree.
		if (MergeTreeXnorHelper(root1, root2)) {
			return root1;
		}

		return root2;
	}
private:
	//true use root1 as new root, false use root2 as new root
	bool MergeTreeXnorHelper(node* root1, node* root2) {
		if (root1->left == nullptr) {
			MergeTreeXnorHelper(root2, root1->is_one);
			return false;
		}

		if (root2->left == nullptr) {
			MergeTreeXnorHelper(root1, root2->is_one);
			return true;
		}

		MergeTreeXnorHelper(root1->left, root2->left);
		return MergeTreeXnorHelper(root1->right, root2->right);
	}

	void MergeTreeXnorHelper(node* root, bool is_one) {
		if (root->left == nullptr) {
			root->is_one = root->is_one == is_one;
			return;
		}
		MergeTreeXnorHelper(root->left, is_one);
		MergeTreeXnorHelper(root->right, is_one);
	}
};

int main() {
	node r1(false);
	node r2(false);
	node n11(false);
	node n12(true);
	node n21(false);
	node n22(false);
	node n23(true);
	node n24(false);
	node n25(false);
	node n26(true);

	r1.left = &n11;
	r1.right = &n12;

	r2.left = &n21;
	r2.right = &n22;
	n21.left = &n23;
	n21.right = &n24;
	n22.left = &n25;
	n22.right = &n26;

	Solution s;
	s.MergeTreeXnor(&r1, &r2);
}