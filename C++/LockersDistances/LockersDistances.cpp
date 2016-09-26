#include <vector>
#include <utility>
#include <queue>

using namespace std;

vector<vector<int>> getLockerDistanceGrid(int length, int width, vector<pair<int, int>>& locker_idx) {
	const vector<pair<int, int>> directions = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
	vector<vector<int>> res(length, vector<int>(width, -1));
	queue<pair<int, int>> q;
	int s = locker_idx.size();
	for (int i = 0; i < s; ++i) {
		res[locker_idx[i].first][locker_idx[i].second] = 0;
		q.emplace(locker_idx[i].first, locker_idx[i].second);
	}
	while (!q.empty()) {
		int ls = q.size();
		for (int i = 0; i < ls; ++i) {
			auto cur = q.front();
			q.pop();
			for (const auto& d : directions) {
				auto next = pair<int, int>(cur.first + d.first, cur.second + d.second);
				if (next.first < length && next.first >= 0 && next.second < width && next.second >= 0 && res[next.first][next.second] == -1) {
					res[next.first][next.second] = res[cur.first][cur.second] + 1;
					q.push(move(next));
				}
			}
		}
	}
	return res;
}

int main() {
	vector<pair<int, int>> test1 = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 6, 5 } };
	getLockerDistanceGrid(10, 7, test1);
}