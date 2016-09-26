#include <unordered_map>
#include <algorithm>
#include <vector>
#include <memory>

using namespace std;

class Solution {
public:
	pair<int, string> winSequence(vector<string> &dict) {
		buildTrie(dict);
		auto res = calculateMinimax(root_, true);
		reverse(res.second.begin(), res.second.end());
		bool play_fist_win = res.first > 0;
		return pair<int, string>(play_fist_win, res.second);
	}

private:
	struct TrieNode {
		bool isWord = false;
		unordered_map<char, shared_ptr<TrieNode>> children;
	};

	void buildTrie(const vector<string> &dict) {
		root_ = make_shared<TrieNode>();
		for_each(dict.begin(), dict.end(), [&](const string& s){insertTrie(s); });
	}

	void insertTrie(const string& word) {
		shared_ptr<TrieNode> cur = root_;
		for (const char & c : word) {
			if (cur->children.find(c) == cur->children.end()) {
				cur->children[c] = make_shared<TrieNode>();
			}
			cur = cur->children[c];
		}
		cur->isWord = true;
	}

	pair<int, string> calculateMinimax(shared_ptr<TrieNode> root, bool fp_turn) {
		if (root->children.empty()) {
			return !fp_turn ? pair<int, string>(-10, "") : pair<int, string>(10, "");
		}
		int minimax_val = fp_turn ? INT_MIN : INT_MAX;
		string sequence;
		for_each(root->children.begin(), root->children.end(), 
			[&](pair<char, shared_ptr<TrieNode>> c){
				auto res = calculateMinimax(c.second, !fp_turn);
				if (fp_turn) {
					if (res.first > minimax_val) {
						minimax_val = res.first;
						sequence = res.second + c.first;
					}
				}
				else {
					if (res.first < minimax_val) {
						minimax_val = res.first;
						sequence = res.second + c.first;
					}
				}
				
			}
		);
		return pair<int, string>(minimax_val, sequence);
	}

	shared_ptr<TrieNode> root_;
};

int main() {
	Solution s;
	vector<string> test1 = { "cat", "cool" };
	vector<string> test2 = { "catfur", "catfood" };
	s.winSequence(test1);
	s.winSequence(test2);
}