/*
* LeetCode OJ #200
*/

#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
	int numIslands(vector<vector<char>>& grid) {
		if (grid.empty()) {
			return 0;
		}
		if (grid[0].empty()) {
			return 0;
		}
		const int h = grid.size();
		const int w = grid[0].size();
		const vector<pair<int, int>> directions{ { 0, -1 }, { 0, 1 },
		{ -1, 0 }, { 1, 0 } };
		int number = 0;
		unordered_map<int, int> set;
		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				if (grid[y][x] == '0') {
					continue;
				}

				auto node = make_pair(y, x);
				set[node_id(node, w)] = node_id(node, w);
				++number;

				for (const auto& d : directions) {
					auto neighbor = make_pair(y + d.first, x + d.second);
					if (neighbor.first >= 0 && neighbor.first < h &&
						neighbor.second >= 0 && neighbor.second < w &&
						set.find(node_id(neighbor, w)) != set.end()) {
						if (find_set(set, node_id(node, w)) !=
							find_set(set, node_id(neighbor, w))) {
							// Merge different islands.
							union_set(set, node_id(node, w), node_id(neighbor, w));
							--number;
						}
					}
				}
			}
		}
		return number;
	}

	int node_id(const pair<int, int>& node, const int w) {
		return node.first * w + node.second;
	}

	void union_set(unordered_map<int, int>& set, int x, int y) {
		int p_x = find_set(set, x);
		int p_y = find_set(set, y);
		set[min(p_x, p_y)] = max(p_x, p_y);
	}

	int find_set(unordered_map<int, int>& set, int x) {
		if (set[x] != x) {
			set[x] = find_set(set, set[x]);
		}
		return set[x];
	}
};

int main() {
	Solution s;
	vector<vector<char>> test1 = { { '1', '1' } };
	s.numIslands(test1);
}