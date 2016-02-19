/*
* see http://www.lintcode.com/en/problem/word-ladder-ii/ for problem description
*/
#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <string> 
#include <algorithm>

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
		unordered_set<string> visitedHash;
		vector<vector<string>> res;
		size_t shortest = INT_MAX;

		visited.push_back(start);
		visitedHash.insert(start);

		findLaddersHelper(res, visited, visitedHash, start, end, dict, shortest);

		return res;
	}

	void findLaddersHelper(vector<vector<string>> &res, vector<string> &visited, unordered_set<string> &visitedHash, string cur, string &end, unordered_set<string> &dict, size_t &shortest) {

		if (visited.size() > shortest) {
			return;
		}

		if (cur == end) {
			shortest = min(visited.size(), shortest);
			for (auto it = res.begin(); it != res.end();)
			{
				if (it->size() > shortest)
					it = res.erase(it);
				else
					++it;
			}
			res.push_back(visited);
			return;
		}

		if (visited.size() == dict.size()) {
			return;
		}

		for (int i = 0; i < end.size(); ++i) {
			char tmp = cur[i];
			for (char c = 'a'; c <= 'z'; ++c) {
				cur[i] = c;
				if (visitedHash.find(cur) == visitedHash.end() && dict.find(cur) != dict.end()) {
					visited.push_back(cur);
					visitedHash.insert(cur);
					findLaddersHelper(res, visited, visitedHash, cur, end, dict, shortest);
					visitedHash.erase(cur);
					visited.pop_back();
				}
				cur[i] = tmp;
			}
		}	
	}
};

int main() {
	Solution s;

	unordered_set<string> dict1 = { "hot", "cog", "dog", "tot", "hog", "hop", "pot", "dot" };
	unordered_set<string> dict2 = { "frye", "heat", "tree", "thee", "game", "free", "hell", "fame", "faye" };
	vector<vector<string>> res1 = s.findLadders("hot", "dog", dict1);
	vector<vector<string>> res2 = s.findLadders("game", "thee", dict2);

	return 0;
}