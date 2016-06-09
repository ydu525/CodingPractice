#include <vector>

using namespace std;

class Solution {
public:
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		const char kSpacer = ' ';
		vector<string> res;
		int s = words.size();
		int curWidth = 0;
		for (int i = 0; i < s; ++i) {
			for (int j = i; j < s; ++j) {
				int ws = words[j].size();
				if (curWidth + ws > maxWidth) {
					string tmp;
					int spaces = maxWidth - curWidth;
					if (j - i == 1) {
						tmp.append(words[i]).append(spaces + 1, kSpacer);
					}
					else {
						vector<int> dis = distributeSpaces(spaces, j - i);
						for (int k = i; k < j - 1; ++k) {
							tmp.append(words[k]).append(dis[k - i], kSpacer);
						}
						tmp.append(words[j - 1]);
					}
					res.push_back(tmp);
					i = j - 1;
					curWidth = 0;
					break;
				}
				else {
					curWidth += ws + 1;
				}
			}
			if (curWidth > 0) {
				string tmp;
				int spaces = maxWidth - curWidth;
				for (int j = i; j < s - 1; ++j) {			
					tmp.append(words[j]).append(1, kSpacer);
				}
				tmp.append(words[s - 1]).append(spaces + 1, kSpacer);
				res.push_back(tmp);
				break;
			}
		}

		return res;
	}
private:
	vector<int> distributeSpaces(int spaces, int words) {
		spaces += words;
		--words; //skip last word
		vector<int> res(words, 0);
		while (spaces > 0) {
			for (auto& s : res) {
				if (spaces == 0) {
					break;
				}
				++s;
				--spaces;
			}
		}
		return res;
	}
};

int main() {
	Solution s;
	vector<string> test1 = { "This", "is", "an", "example", "of", "text", "justification." };
	s.fullJustify(test1, 16);
	return 0;
}