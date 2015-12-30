/*
* see http://www.lintcode.com/en/problem/wildcard-matching/ for problem description
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
		else if (*s == *p || *p == '?') {
			return isMatch(s + 1, p + 1);
		}
		else if (*p == '*') {
			//return isMatch(s, p + 1) || isMatch(s + 1, p) || isMatch(s + 1, p + 1);
			while (*s != 0) {
				if (isMatch(s, p + 1)) {
					return true;
				}
				++s;
			}
			return isMatch(s, p + 1);
		}
		//else if (*s != *p) {
		//    return false;
		//}

		return false;
	}
};

int main() {
	Solution s;

	char w1[] = { 'a', 'a', '\0' };
	char w2[] = { 'a', 'a', 'a', '\0' };
	char w3[] = { '*', '\0' };
	char w4[] = { 'a', '*', '\0' };
	char w5[] = { '?', '*', '\0' };

	bool match = s.isMatch(w1, w2);
	match = s.isMatch(w1, w3);
	match = s.isMatch(w1, w4);
	match = s.isMatch(w1, w5);

	return 0;
}