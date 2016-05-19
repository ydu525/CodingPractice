/*
 * https://www.careercup.com/question?id=5723093194506240
 */
 
#include <unordered_map>
#include <vector>
 
using namespace std;
 
class Solution {
public:
	int findOverallTime(const vector<string>& tasks, int k) {
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
				} else {
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
	vector<string> test1 = "aaabccb";
	Solution s;
	cout << s.findOverallTime(test1, 3) << endl;
}