#include <string>
#include <sstream> 
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int val) {
		this->val = val;
		this->left = this->right = nullptr;		
	}
};

class Solution {
public:
	TreeNode* findMaxLengthIdenticalSubtrees(TreeNode* root) {
		//string str_tree = serialize(root);
		unordered_map<hashNode, int, MyHash> id_map;
		unordered_map<int, TreeNode*> id_to_node;
		int max_id = 0;
		helper(root, id_map, id_to_node, max_id);
		if (!max_id) {
			return nullptr;
		}
		return id_to_node[max_id];
	}
	
private:
	struct hashNode {
		int left_id;
		int right_id;
		int val;
		hashNode(int l_id, int r_id, int v) : left_id(l_id), right_id(r_id), val(v) {}
		bool operator==(const hashNode& rhs) const{
			return this->left_id == rhs.left_id && this->right_id == rhs.right_id && this->val == rhs.val;
		}
	};

	struct MyHash {
		inline size_t operator()(const hashNode& p) const {
			return (7 * hash<int>()(p.left_id) + 13 * hash<int>()(p.right_id) + hash<int>()(p.val));
		}
	};

	int helper(TreeNode* root, unordered_map<hashNode, int, MyHash>& id_map, unordered_map<int, TreeNode*>& id_to_node, int& max_id) {
		if (root == nullptr) {
			return 0;
		}
		int left_id = helper(root->left, id_map, id_to_node, max_id);
		int right_id = helper(root->right, id_map, id_to_node, max_id);
		hashNode tmp(left_id, right_id, root->val);
		int id = max(left_id, right_id) + 1;
		if (id_map.find(tmp) == id_map.end()) {
			id_to_node[id] = root;	
			id_map[tmp] = id;
		}
		else {
			max_id = max(max_id, id);
		}
		return id_map[tmp];
	}
};

TreeNode *deserializeHelper(istringstream& in) {
	string val;
	in >> val;
	if (val == "#") {
		return nullptr;
	}
	else {
		TreeNode* root = new TreeNode(stoi(val));
		root->left = deserializeHelper(in);
		root->right = deserializeHelper(in);
		return root;
	}
}

TreeNode *deserialize(string data) {
	istringstream in(data);  // Space: O(n)
	return deserializeHelper(in);
}

int main()
{
	TreeNode *test1 = deserialize("5 4 # # 4 # #"); 
	TreeNode *test2 = deserialize("5 4 3 # # # 4 3 # # #");
	Solution s;
	s.findMaxLengthIdenticalSubtrees(test1);
	s.findMaxLengthIdenticalSubtrees(test2);
	return 0;
}