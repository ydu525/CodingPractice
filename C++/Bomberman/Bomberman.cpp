#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class Solution {
public:
	//0 empty
	//1 enemy
	//-1 wall
	int mostKills(const vector<vector<int>>& board) {
		int res = 0;
		int m = board.size();
		if (m == 0) {
			return res;
		}
		int n = board[0].size();
		if (n == 0) {
			return res;
		}
		vector <vector<pair<int, int>>> f(m + 1, vector<pair<int, int>>(n + 1, pair<int, int>(-1, -1)));
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (board[i - 1][j - 1] == -1) {
					continue;
				}
				if (f[i][j - 1].second == -1) {
					f[i][j].second = 0;
					int k = j;
					while (k <= n && board[i - 1][k - 1] != -1) {
						f[i][j].second += board[i - 1][k - 1];
						++k;
					}
				}
				else {
					f[i][j].second = f[i][j - 1].second;
				}
				if (f[i - 1][j].first == -1) {
					f[i][j].first = 0;
					int k = i;
					while (k <= m && board[k - 1][j - 1] != -1) {
						f[i][j].first += board[k - 1][j - 1];
						++k;
					}
				}
				else {
					f[i][j].first = f[i - 1][j].first;
				}
				if (board[i - 1][j - 1] == 0) {
					res = max(res, f[i][j].first + f[i][j].second);
				}
			}		
		}
		return res;
	}
};

int main() {
	vector<vector<int>> board1 = { { 0, 0, 1, 1, -1 }, { 1, 1, -1, 0, 0 }, { 0, -1, 0, 0, 1 }, { 1, 1, 1, 1, 1 } };
	Solution s;
	s.mostKills(board1);
	return 0;
}