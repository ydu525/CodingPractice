/*
 * Given a src, a dst and a matrix. Each element in the matrix is the height of a bar. From day 0, the amount of rain will increase by 1 each day.
 * When the amount of rain is greater than the height of a bar, that bar will be overflowed. Find the earliest day that the water will be connected from src to dst.
 */
#include <utility>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
	//please note the height of the bar at src is assumed to be the lowest in the matrix.
	//if not, some modifications has to be made.
	//probably find the lowest height first before running main logic
	int leastDays(const pair<int, int>& src, const pair<int, int>& dst, const vector<vector<int>>& matrix) const {
		const vector<pair<int, int>> directions{ { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
		int n = matrix.size();
		if (n == 0) {
			return 0;
		}
		int m = matrix.size();
		if (m == 0) {
			return 0;
		}
		int highest = 0;
		auto comp = [&](const node& rhs, const node& lhs){ return rhs.value != lhs.value ? rhs.value > lhs.value : rhs.index > lhs.index; };
		unordered_set<pair<int, int>, MyHash> visited;
		priority_queue<node, vector<node>, decltype(comp)> q;

		visited.insert(src);
		q.emplace(src, matrix[src.first][src.second]);
		while (!q.empty()) {
			auto p = q.top();
			q.pop();
			if (p.value > highest) {
				highest = p.value;
			}
			for (const auto& d : directions) {
				pair<int, int> next(p.index.first + d.first, p.index.second + d.second);
				if (next.first >= 0 && next.first < n && next.second >= 0 && next.second < m && visited.find(next) == visited.end()) {
					if (next == dst) {
						highest = max(highest, matrix[dst.first][dst.second]);
						return highest + 1;
					}
					int next_value = matrix[next.first][next.second];
					q.emplace(next, next_value);
					visited.insert(next);
				}
			}
		}
		return highest + 1;
	}

private:
	struct MyHash {
		inline std::size_t operator()(const std::pair<int, int>& p) const {
			return (hash<int>()(p.first) + hash<int>()(p.second));
		}
	};

	struct node {
		pair<int, int> index;
		int value;
		node(pair<int, int> idx, int val) : index(idx), value(val) {}
	};
};

int main() {
	vector<vector<int>> m1 = { { 1, 3, 2, 4 }, { 2, 7, 5, 11 }, { 12, 13, 7, 8 }, { 1, 2, 9, 4 } };
	Solution s;
	pair<int, int> src(0, 0);
	pair<int, int> dst(3, 3);
	s.leastDays(src, dst, m1);
	return 0;
}