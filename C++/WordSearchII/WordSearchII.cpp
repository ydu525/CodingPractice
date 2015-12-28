/*
 * see http://www.lintcode.com/en/problem/word-search-ii/ for problem description
 */
#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>

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

	// We can use search to find out wheter a word is in the dictionary
	// By doing that, each time we search a word, it will start at the root of the trie
	// Since we are doing recursion and backtracking with our main solution, we want to keep a record of our prefix
	//	and it will make looking out word faster
	// This function will take a pointer to a Trie node, if the passed-in node contains the passed-in character
	//	we return that child node, otherwise we return null
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
		unordered_set<string> res;
		string str;

		int h = board.size();
		int w = board[0].size();

		vector<vector<bool>> visited(h, vector<bool>(w, false));

		for (string &w : words) {
			trie.insert(w);
		}

		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
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

		vector<string> resv;
		for (auto it = res.begin(); it != res.end(); ++it) {
			resv.push_back(*it);
		}

		return resv;
	}

	void wordSearchIIHelper(unordered_set<string> &res, string &str, TrieNode* pre, Trie &trie, int y, int x, vector<vector<char> > &board, vector<vector<bool>> &visited) {
		if (trie.isWord(pre)) {
			if (res.find(str) == res.end()) {
				res.insert(str);
			}
		}

		if (visited[y][x]) {
			return;
		}

		visited[y][x] = true;

		const vector<int> n = { 0, -1, 1, 0 };
		const vector<int> m = { -1, 0, 0, 1 };

		int h = board.size();		//height
		int w = board[0].size();	//width

		int mx, ny;
		for (int i = 0; i < 4; ++i) {
			mx = x + m[i];
			ny = y + n[i];

			if (mx >= 0 && mx < w && ny >= 0 && ny < h && !visited[ny][mx]) {
				TrieNode* cur = trie.findNext(pre, board[ny][mx]);
				if (cur == NULL) {
					continue;
				}
				else {
					str.push_back(board[ny][mx]);
					wordSearchIIHelper(res, str, cur, trie, ny, mx, board, visited);
					str.pop_back();
				}
			}
		}
		visited[y][x] = false;
	}
};

int main() {
	Solution s;
	vector<vector<char> > board = { { 'd', 'o', 'a', 'f' }, { 'a', 'g', 'a', 'i' }, { 'd', 'c', 'a', 'n' } };
	vector<string> dict = { "dog", "dad", "dgdg", "can", "again" };
	vector<string> res = s.wordSearchII(board, dict);

	board = { { 'a', 'b', 'c', 'e' }, { 's', 'f', 'c', 's' }, { 'a', 'd', 'e', 'e' } };
	dict = { "se", "see" };
	res = s.wordSearchII(board, dict);

	return 0;
}