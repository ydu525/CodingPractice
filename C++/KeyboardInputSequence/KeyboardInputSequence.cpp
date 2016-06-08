/*
 * Given a virtual keyboard layout and a string. You only have 5 buttons, up, down, left, right and confirm.
 * Return a string representing the input sequence into the keyboard to match the given string.
 *	for example the keyboard looks like below
 *	a b c d e f g h
 *	i j k l m n o p
 *	q r s t u v w x
 *	y z
 *	the start postion of cursor is at a, the string is "boy".
 *	the input sequence is "r x r r r r r d x l l l l l l d d x".
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	string inputSequence(string in, char start) {
		string res = "";
		for (const char& c : in) {
			int pos_start = start - 'a';
			int pos_end = c - 'a';
			int horizontal_moves = pos_start % kNum - pos_end % kNum;
			int vertical_moves = pos_end / kNum - pos_start / kNum;

			if (vertical_moves < 0) {
				//move vertically first
				vertical_moves = -vertical_moves;
				for (int i = 0; i < vertical_moves; ++i) {
					res.push_back(kUp);
				}
				moveHorizontally(res, horizontal_moves);
			}
			else {
				//move horizontally first
				moveHorizontally(res, horizontal_moves);
				for (int i = 0; i < vertical_moves; ++i) {
					res.push_back(kDown);
				}
			}
			start = c;
			res.push_back(kConfirm);
		}
		return res;
	}

private:
	const char kUp = 'u';
	const char kDown = 'd';
	const char kLeft = 'l';
	const char kRight = 'r';
	const char kConfirm = 'x';
	const int kNum = 8;

	void moveHorizontally(string &res, int horizontal_moves) {
		if (horizontal_moves < 0) {
			horizontal_moves = -horizontal_moves;
			for (int i = 0; i < horizontal_moves; ++i) {
				res.push_back(kRight);
			}
		}
		else {
			for (int i = 0; i < horizontal_moves; ++i) {
				res.push_back(kLeft);
			}
		}
	}
};

int main()
{
	Solution s;
	while (1) {
		std::string input;
		std::cout << "What is your input? ";
		getline(std::cin, input);
		std::cout << s.inputSequence(input, 'a') << "\n";
	}
}
