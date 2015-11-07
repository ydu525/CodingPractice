#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

/**
* @param s A string
* @return whether the string is a valid parentheses
*/


bool isValidParenthesesH(const string &s, int &i) {

	int levelHolder = 0;

	while (i < (int)s.size()) {
		if (s[i] == '(') {
			if (!levelHolder) {
				levelHolder = 1;
				++i;
			}
			else {
				if (isValidParenthesesH(s, i)) {
					++i;
				}
				else {
					return false;
				}
			}

		}
		else if (s[i] == ')') {
			if (levelHolder == 1) {
				levelHolder = 0;
			}
			else {
				return false;
			}
		}
		else if (s[i] == '[') {
			if (!levelHolder) {
				levelHolder = 2;
				++i;
			}
			else {
				if (isValidParenthesesH(s, i)) {
					++i;
				}
				else {
					return false;
				}
			}
		}
		else if (s[i] == ']') {
			if (levelHolder == 2) {
				levelHolder = 0;
			}
			else {
				return false;
			}
		}
		else if (s[i] == '{') {
			if (!levelHolder) {
				levelHolder = 3;
				++i;
			}
			else {
				if (isValidParenthesesH(s, i)) {
					++i;
				}
				else {
					return false;
				}
			}
		}
		else { //if(s[i] == '}') {
			if (levelHolder == 3) {
				levelHolder = 0;
			}
			else {
				return false;
			}
		}
	}

	if (!levelHolder)
		return true;
	else
		return false;
}

bool isValidParentheses(string& s) {
	// Write your code here
	if (s.size() == 0) {
		return true;
	}

	int start = 0;

	return isValidParenthesesH(s, start);
}

bool isValidParentheses2(string& s) {
	const  unordered_map<char, char> symbol_pair = { { ')', '(' },
	{ ']', '[' },
	{ '}', '{' } };
	stack<char> parentheses;
	for (const auto& c : s) {
		const auto& it = symbol_pair.find(c);
		if (it != symbol_pair.cend()) {
			if (parentheses.empty() ||
				parentheses.top() != it->second) {
				return false;
			}
			parentheses.pop();
		}
		else {
			parentheses.emplace(c);
		}
	}
	return parentheses.empty();
}


int main() {
	string s = "()";

	bool check = isValidParentheses2(s);

	return 0;
}