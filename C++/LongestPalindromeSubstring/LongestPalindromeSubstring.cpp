/*
 * see http://www.lintcode.com/en/problem/longest-palindromic-substring/ for problem description
 */
#include <vector>
#include <string>
#include <iostream>

using namespace std;

string findLongestPalindromicSubstring(const string& input) {

	int size = static_cast<int>(input.size());
	string res = "";
	vector<vector<bool>> f(size, vector<bool>(size, false));

	if (input.empty()) {
		return res;
	}

	//substring with length 1 is palindrome
	int maxLength = 1;
	int diff, start = 0;
	for (int i = 0; i < size; ++i)
		f[i][i] = true;

	for (int i = 1; i < size; ++i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			diff = i - j;

			if ((f[j + 1][i - 1] || diff == 1) && input[i] == input[j])
			{
				f[j][i] = true;

				if (++diff > maxLength)
				{
					start = j;
					maxLength = diff;
				}
			}
		}
	}

	res = input.substr(start, maxLength);

	return res;
}

int main() {

	string str;
	if (findLongestPalindromicSubstring(str) == "") {
		cout << "test 0 passed" << endl;
	}
	else {
		cout << "test 0 failed" << endl;
	}

	if (findLongestPalindromicSubstring("abc") == "a") {
		cout << "test 1 passed" << endl;
	}
	else {
		cout << "test 1 failed" << endl;
	}

	if (findLongestPalindromicSubstring("aabbcc") == "aa") {
		cout << "test 2 passed" << endl;
	}
	else {
		cout << "test 2 failed" << endl;
	}

	if (findLongestPalindromicSubstring("aacbabc") == "cbabc") {
		cout << "test 3 passed" << endl;
	}
	else {
		cout << "test 3 failed" << endl;
	}

	if (findLongestPalindromicSubstring("aacbaabc") == "cbaabc") {
		cout << "test 4 passed" << endl;
	}
	else {
		cout << "test 4 failed" << endl;
	}

	if (findLongestPalindromicSubstring("aacbaabcet") == "cbaabc") {
		cout << "test 5 passed" << endl;
	}
	else {
		cout << "test 5 failed" << endl;
	}

	if (findLongestPalindromicSubstring("aacbaabcetget") == "cbaabc") {
		cout << "test 6 passed" << endl;
	}
	else {
		cout << "test 6 failed" << endl;
	}

	return 0;
}