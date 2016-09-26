#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <memory>

using namespace std;

class Solution {
public:
	Solution(const vector<string>& dict) {
		buildTrie(dict);
	}	

	vector<string> findMatches(const string& pattern) {
		vector<string> res;
		string cur;
		if (pattern.empty()) {
			return res;
		}
		findMatchesHelper(root_, pattern, 0, cur, res);
		return res;
	}

private:
	struct TrieNode {
		bool is_word = false;
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
		cur->is_word = true;
	}

	void findMatchesHelper(shared_ptr<TrieNode> root, const string& pattern, int idx, string& cur, vector<string>& res) {
		const int s = pattern.size();
		if (idx >= s && root->is_word) {
			res.push_back(cur);
		}

		for (auto it = root->children.begin(); it != root->children.end(); ++it) {
			if (idx < s && it->first == pattern[idx]) {
				cur.push_back(it->first);
				findMatchesHelper(it->second, pattern, idx + 1, cur, res);
				cur.pop_back();
			}
			else {
				if (islower(it->first) && (idx >= s || isupper(pattern[idx]))) {
					cur.push_back(it->first);
					findMatchesHelper(it->second, pattern, idx, cur, res);
					cur.pop_back();
				}
			}
		}
	}

	shared_ptr<TrieNode> root_;
};

int main() {
	vector<string> dict = { "CaaaC", "CaaaK", "CaaaCa", "CaaaCabcdefgh", 
		"CaaaCabcdefghI", "CbbbbbC", "CabK", "CabbbbbbbCK", "CabbbbbC",
		"caxxxxxxxxxxxxxxxxxxxxxxxxxxxxxK", "AbbbCddddEffff" };
	Solution s(dict);
	s.findMatches("CC");
	s.findMatches("CaC");
	s.findMatches("A");
	s.findMatches("c");
	s.findMatches("ACE");
	s.findMatches("AbCE");
	s.findMatches("ACdE");
	s.findMatches("ACEf");
	s.findMatches("CaaadC");
}