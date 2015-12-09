/*
 * see http://www.lintcode.com/en/problem/word-search-ii/ for problem description
 */
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class TrieNode {
public:
	// Initialize your data structure here.
	TrieNode() {
		exists = false;
	}

	unordered_map<char, TrieNode*> childs;
	bool exists;
};

class Trie {
public:
	Trie() {
		root = new TrieNode();
	}

	// Inserts a word into the trie.
	void insert(string word) {
		TrieNode *cur = root;
		for (char & c : word) {
			if (cur->childs.find(c) == cur->childs.end()) {
				cur->childs[c] = new TrieNode();
			}

			cur = cur->childs[c];
		}
		cur->exists = true;
	}

	// Returns if the word is in the trie.
	bool search(string word) {
		TrieNode *cur = root;
		for (char & c : word) {
			if (cur->childs.find(c) == cur->childs.end()) {
				return false;
			}
			else {
				cur = cur->childs[c];
			}
		}
		if (cur->exists) {
			return true;
		}
		return false;
	}

	TrieNode* findNext(TrieNode* curPrefix, char nextChar) {
		TrieNode* cur = curPrefix;
		if (cur == NULL) {
			cur = root;
		}
		if (cur->childs.find(nextChar) == cur->childs.end()) {
			return NULL;
		}
		return cur->childs[nextChar];
	}

	bool isWord(TrieNode* curPrefix) {
		return curPrefix->exists;
	}

private:
	TrieNode* root;
};

class Solution {
public:
	/**
	* @param board: A list of lists of character
	* @param words: A list of string
	* @return: A list of string
	*/
	vector<string> wordSearchII(vector<vector<char> > &board, vector<string> &words) {
		// write your code here
		//build trie
		Trie trie;
		vector<string> res;
		string str;

		int w = board.size();//h
		int h = board[0].size();//w

		vector<vector<bool>> visited(w, vector<bool>(h, false));

		for (string &w : words) {
			trie.insert(w);
		}

		for (int i = 0; i < w; ++i) {
			for (int j = 0; j < h; ++j) {
				TrieNode* cur = trie.findNext(NULL, board[i][j]);
				if (cur == NULL) {
					continue;
				}
				else {
					str.push_back(board[i][j]);
					wordSearchIIHelper(res, str, cur, trie, i, j, board, visited);
					str.pop_back();
				}
			}
		}

		return res;
	}

	void wordSearchIIHelper(vector<string> &res, string &str, TrieNode* pre, Trie &trie, int x, int y, vector<vector<char> > &board, vector<vector<bool>> &visited) {
		if (trie.isWord(pre)) {
			res.push_back(str);
			return;
		}

		if (visited[x][y]) {
			return;
		}

		visited[x][y] = true;

		const vector<int> m = { 0, -1, 1, 0 };
		const vector<int> n = { -1, 0, 0, 1 };

		int w = board.size();//h
		int h = board[0].size();//w

		int mx, ny;
		for (int i = 0; i < 4; ++i) {
			mx = x + m[i];
			ny = y + n[i];

			if (mx >= 0 && mx < w && ny >= 0 && ny < h && !visited[mx][ny]) {
				TrieNode* cur = trie.findNext(pre, board[mx][ny]);
				if (cur == NULL) {
					continue;
				}
				else {
					str.push_back(board[mx][ny]);
					wordSearchIIHelper(res, str, cur, trie, mx, ny, board, visited);
					str.pop_back();
				}
			}
		}
		visited[x][y] = false;
	}
};

int main() {
	Solution s;
	vector<vector<char> > board = { { 'd', 'o', 'a', 'f' }, { 'a', 'g', 'a', 'i' }, { 'd', 'c', 'a', 'n' } };
	vector<string> dict = { "dog", "dad", "dgdg", "can", "again" };
	vector<string> res = s.wordSearchII(board, dict);
	return 0;
}