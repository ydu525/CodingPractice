/*
* see http://www.lintcode.com/en/problem/restore-ip-addresses/ for problem description
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
	* @param s the IP string
	* @return All possible valid IP addresses
	*/
	vector<string> restoreIpAddresses(string& s) {
		// Write your code here
		vector<string> res;
		vector<int> curNums;
		restoreIpAddressesHelper(curNums, 0, res, s);

		return res;
	}

	void restoreIpAddressesHelper(vector<int> &curNums, int start, vector<string> &res, string &s) {
		const int maxIP = 255;
		const int maxDigits = 3;
		const int maxDots = 4;

		int l = s.size();
		int dc = curNums.size();

		if (dc == maxDots) {
			string tmp;
			for (int i = 0; i < dc; ++i) {
				tmp.append(to_string(curNums[i]));
				tmp.push_back('.');
			}
			tmp.pop_back();
			res.push_back(tmp);
			return;
		}

		for (int i = 1; i <= maxDigits & start + i <= l; ++i) {
			//pruning - continue when the dots left can't cover the digits left
			if (l - start - i > (maxDots - dc - 1) * maxDigits) {
				continue;
			}
			int num = stoi(s.substr(start, i));
			if (num > maxIP) {
				return;
			}
			curNums.push_back(num);
			restoreIpAddressesHelper(curNums, start + i, res, s);
			curNums.pop_back();
		}
	}
};

int main() {
	Solution s;

	vector<string> res = s.restoreIpAddresses(string("25525511135"));
	res = s.restoreIpAddresses(string("0000"));
	res = s.restoreIpAddresses(string("255255255255"));

	return 0;
}