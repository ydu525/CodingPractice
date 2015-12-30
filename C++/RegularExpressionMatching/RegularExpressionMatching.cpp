/*
* see http://www.lintcode.com/en/problem/regular-expression-matching/ for problem description
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
	* @param s: A string
	* @param p: A string includes "?" and "*"
	* @return: A boolean
	*/
	bool isMatch(const char *s, const char *p) {
		// write your code here
		if (*s == 0 && *p == 0) {
			return true;
		}
		else if (*s == 0 || *p == 0) {
			return false;
		}

		if (*s == *p || *p == '.') {
			if (*(p + 1) != '*') {
				return isMatch(s + 1, p + 1);
			}
			else {
				return isMatch(s, p + 2) || isMatch(s + 1, p) || isMatch(s + 1, p + 2);
			}
		}
		else if (*(p + 1) == '*') {
			return isMatch(s, p + 2);
		}

		return false;
	}
};

int main() {
	Solution s;

	char w1[] = { 'a', 'a', '\0' };
	char w2[] = { '.', '*', '\0' };
	char w3[] = { 'a', 'b', '\0' };
	char w4[] = { 'a', 'a', 'b', '\0' };
	char w5[] = { 'c', '*', 'a', '*', 'b', '\0' };

	bool match = s.isMatch(w1, w2);
	match = s.isMatch(w3, w2);
	match = s.isMatch(w4, w5);

	return 0;
}