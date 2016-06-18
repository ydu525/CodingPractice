/*
 * Given a src, a dst and a matrix. Each element in the matrix represents the height. You have a helicopter fly from src to dst. The helicopter can not move from a higher height position
 * to a lower height position. In another words, the height of next position >= the height of current position. Return the sum of the heights of a route from src to dst which is the minimum among all.
 */
#include <utility>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class Solution {
public:
	int minimumHeightsSum(const pair<int, int>& src, const pair<int, int>& dst, const vector<vector<int>>& matrix) const {
		const vector<pair<int, int>> directions{ { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
		int sum = 0;
		int n = matrix.size();
		if (n == 0) {
			return 0;
		}
		int m = matrix.size();
		if (m == 0) {
			return 0;
		}

		unordered_map<int, int> visited;			//key: index, value: cumulated sum
		//below two data structue simulate hash heap
		unordered_map<int, MyHeap::iterator> hash;	//key: index, value: position of index in heap
		MyHeap heap;								//key: cumulated sum, value: index

		int src_index = src.first * n + src.second;
		int dst_index = dst.first * n + dst.second;
		visited[src_index] = matrix[src.first][src.second];
		auto res_it = heap.emplace(visited[src_index], src_index);
		hash[src_index] = res_it;
		while (!heap.empty()) {
			auto cur_it = heap.begin();
			int cur_sum = cur_it->first;
			int cur_x = cur_it->second / n;
			int cur_y = cur_it->second % n;
			for (const auto& d : directions) {
				int next_x = cur_x + d.first;
				int next_y = cur_y + d.second;
				int next_index = next_x * n + next_y;
				if (next_x >= 0 && next_x < n && next_y >= 0 && next_y < m && matrix[next_x][next_y] >= matrix[cur_x][cur_y]) {			
					auto v_it = visited.find(next_index);
					if (v_it == visited.end()) { 
						//if next point has not been visited
						int next_sum = cur_sum + matrix[next_x][next_y];
						visited[next_index] = next_sum;
						auto res_it = heap.emplace(visited[next_index], next_index);
						hash[next_index] = res_it;
					}
					else {
						int next_sum = v_it->second;
						if (next_sum > cur_sum + matrix[next_x][next_y]) {
							//if current next_sum > new next_sum
							auto h_it = hash.find(next_index);
							if (h_it != hash.end()) {
								//if next point is already in heap
								heap.erase(h_it->second);
							}
							visited[next_index] = cur_sum + matrix[next_x][next_y];
							auto res_it = heap.emplace(visited[next_index], next_index);
							hash[next_index] = res_it;
						}
					}
					if (next_index == dst_index) {
						return visited[dst_index];
					}
				}
			}
			hash.erase(cur_it->second);
			heap.erase(cur_it);
		}
		return -1;
	}

private:
	using MyHeap = multimap<int, int, less<int>>;
};

int main() {
	vector<vector<int>> m1 = { { 1, 3, 2, 4 }, { 2, 7, 5, 11 }, { 12, 13, 7, 8 }, { 1, 2, 9, 4 } };
	Solution s;
	pair<int, int> src(0, 0);
	pair<int, int> dst(3, 3);
	int res = s.minimumHeightsSum(src, dst, m1);
	return 0;
}