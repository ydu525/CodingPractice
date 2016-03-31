/*
* https://www.careercup.com/question?id=5723093194506240
*/

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
public:
	int findOverallTime(vector<string> tasks, int k) {
		unordered_map<string, int> m;
		int delay = 0;
		int overall = 0;

		for (int i = 0; i < tasks.size(); ++i) {
			auto it = m.find(tasks[i]);
			if (it == m.end()) {
				m.emplace(tasks[i], i + delay);
			} else {
				int pos_suppose = i + delay;
				int pos_actual = it->second + k;
				int diff = pos_actual - pos_suppose;
				if (diff < 0) {
					it->second = i + delay;
				}
				else {
					++diff;
					overall += diff;
					delay += diff;
					it->second = i + delay;
				}
			}
			++overall;
		}
		return overall;
	}
};

int main() {
	Solution s;
	vector<string> tasks1 = { "A", "A", "A" };
	vector<string> tasks2 = { "A", "A", "B" };
	vector<string> tasks3 = { "A", "A", "B", "A" };
	vector<string> tasks4 = { "A", "A", "B", "C", "A" };
	vector<string> tasks5 = { "A", "A", "B", "B", "A" };
	vector<string> tasks6 = { "A", "A", "B", "C", "D", "A" };
	vector<string> tasks7 = { "A", "B", "C" };
	int res = s.findOverallTime(tasks1, 3);
	res = s.findOverallTime(tasks2, 3);
	res = s.findOverallTime(tasks3, 3);
	res = s.findOverallTime(tasks4, 3);
	res = s.findOverallTime(tasks5, 3);
	res = s.findOverallTime(tasks6, 3);
	res = s.findOverallTime(tasks7, 3);
}