/*
* see http://www.lintcode.com/en/problem/word-ladder-ii/ for problem description
*/
#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <string> 

using namespace std;

class Solution {
public:
	/**
	* @param start, a string
	* @param end, a string
	* @param dict, a set of string
	* @return a list of lists of string
	*/
	vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
		// write your code here
		vector<string> visited;
		vector<vector<string>> res;

		visited.push_back(start);

		findLaddersHelper(res, visited, 0, start, end, dict);

		return res;
	}

	void findLaddersHelper(vector<vector<string>> &res, vector<string> &visited, int index, string cur, string &end, unordered_set<string> &dict) {

		if (cur == end) {
			res.push_back(visited);
			return;
		}

		if (index == end.size()) {
			return;
		}

		char tmp = cur[index];
		for (char c = 'a'; c <= 'z'; ++c) {
			if (tmp != c) {
				cur[index] = c;
				if (dict.find(cur) != dict.end()) {
					visited.push_back(cur);
					findLaddersHelper(res, visited, index + 1, cur, end, dict);
					visited.pop_back();
				}
			}
		}
	}
};

int main() {
	Solution s;

	unordered_set<string> dict = { "hot", "dot", "dog", "lot", "log" };
	vector<vector<string>> res = s.findLadders("hit", "cog", dict);

	return 0;
}