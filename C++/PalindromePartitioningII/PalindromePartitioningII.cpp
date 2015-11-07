#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<bool> > getIsPalindrome(string s) {
	vector<vector<bool> > isPalindrome(s.size(), vector<bool>(s.size(), false));

	for (int i = 0; i < s.size(); i++) {
		isPalindrome[i][i] = true;
	}

	for (int i = 0; i < s.size() - 1; i++) {
		isPalindrome[i][i + 1] = (s[i] == s[i + 1]);
	}

	for (int length = 2; length < s.size(); length++) {
		for (int start = 0; start + length < s.size(); start++) {
			isPalindrome[start][start + length]
				= isPalindrome[start + 1][start + length - 1]
				&& s[start] == s[start + length];
		}
	}

	return isPalindrome;
}

int minCut(string s) {
	// write your code here
	vector<vector<bool> > isPalindrome = getIsPalindrome(s);

	vector<int> state(s.size() + 1, 0);

	for (int i = 0; i <= s.size(); i++) {
		state[i] = i - 1;
	}

	for (int i = 1; i <= s.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (isPalindrome[j][i - 1]) {
				state[i] = min(state[i], state[j] + 1);
			}
		}
	}

	return state[s.size()];

}



int main() {
	cout << minCut("bb") << endl;

	return 0;
}