/*
* see http://www.lintcode.com/en/problem/consistent-hashing/ for problem description
*/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
	/**
	* @param n a positive integer
	* @return n x 3 matrix
	*/
	vector<vector<int>> consistentHashing(int n) {
		// Write your code here
		static unordered_map<int, vector<vector<int>>> m;
		if (m.size() < n) {
			for (auto i = m.size(); i < n; ++i) {
				if (i == 0) {
					vector<int> tv = { 0, 359, 1 };
					vector<vector<int>> tvv;
					tvv.emplace_back(move(tv));
					m.emplace(i, move(tvv));
					continue;
				}
				auto it = m.find(i - 1);
				int max_diff = 0;
				int idx;
				int id;
				for (auto j = 0; j < it->second.size(); ++j) {
					int diff = it->second[j][1] - it->second[j][0];
					if (diff > max_diff) {
						max_diff = diff;
						idx = j;
					} else if (diff == max_diff) {
						if (it->second[j][2] < id) {
							idx = j;
							id = it->second[j][2];
						}
					}
				}
				vector<vector<int>> tvv;
				for (auto j = 0; j < it->second.size(); ++j) {
					if (j == idx) {
						vector<int> tv;
						int half = (it->second[j][1] - it->second[j][0]) / 2;
						tv.emplace_back(it->second[j][0]);
						tv.emplace_back(it->second[j][0] + half);
						tv.emplace_back(it->second[j][2]);
						tvv.emplace_back(tv);
						tv[0] = it->second[j][0] + half + 1;
						tv[1] = it->second[j][1];
						tv[2] = i + 1;
						tvv.emplace_back(move(tv));
					}
					else {
						tvv.emplace_back(it->second[j]);
					}
				}
				m.emplace(i, move(tvv));
			}
		}	
		return m[n - 1];
	}
};

int main() {
	Solution s;
	vector<vector<int>> res = s.consistentHashing(1);
	res = s.consistentHashing(2);
	res = s.consistentHashing(5);
	res = s.consistentHashing(3);
}