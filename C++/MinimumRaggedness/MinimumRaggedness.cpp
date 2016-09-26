#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
	int minimumRaggedness(const string& in, int k) {
		if (in.empty()) {
			return 0;
		}
		//return minSquaredSumDFS(in, k, 0);
		//unordered_map<size_t, int> record;
		//return minSquaredSumDFSWithMem(in, k, 0, record);
		return minimumRaggednessDP(in, k);
	}

	int minimumRaggednessDFS(const string& in, int k, size_t start_pos) {
		int space_left = k;
		int res = INT_MAX;
		while (space_left > 0) {
			auto space_pos = in.find(' ', start_pos);
			space_pos = space_pos == string::npos ? in.size() : space_pos;
			space_left = space_left - (space_pos - start_pos);
			if (space_left < 0) {
				break;
			}
			if (space_pos == in.size()) {
				res = min(res, static_cast<int>(pow(space_left, 2)));
				break;
			}
			int child_res = minimumRaggednessDFS(in, k, ++space_pos);
			res = min(res, static_cast<int>(pow(space_left, 2)) + child_res);
			start_pos = space_pos;
			--space_left;
		}	
		return res;
	}

	int minimumRaggednessDFSWithMem(const string& in, int k, size_t start_pos, unordered_map<size_t, int>& record) {
		auto it = record.find(start_pos);
		if (it != record.end()) {
			return it->second;
		}
		auto pos = start_pos;
		int space_left = k;
		int res = INT_MAX;
		while (space_left > 0) {
			auto space_pos = in.find(' ', pos);
			space_pos = space_pos == string::npos ? in.size() : space_pos;
			space_left = space_left - (space_pos - pos);
			if (space_left < 0) {
				break;
			}
			if (space_pos == in.size()) {
				res = min(res, static_cast<int>(pow(space_left, 2)));
				break;
			}
			int child_res = minimumRaggednessDFSWithMem(in, k, ++space_pos, record);
			res = min(res, static_cast<int>(pow(space_left, 2)) + child_res);
			pos = space_pos;
			--space_left;
		}
		record[start_pos] = res;
		return res;
	}

	int minimumRaggednessDP(const string& in, int k) {
		unordered_map<int, size_t> words;
		int i = 0;
		for (size_t start = 0; start < in.size(); ++i) {
			size_t space = in.find(' ', start);
			space = space == string::npos ? in.size() : space;
			words[i] = space - start;
			start = ++space;
		}
		int n = words.size();
		vector<int> DP(n + 1, INT_MAX);
		DP[0] = 0;
		for (int i = 1; i <= n; ++i) {
			int space_left = k - words[i - 1];
			DP[i] = min(DP[i], DP[i - 1] + static_cast<int>(pow(space_left, 2)));
			--space_left;
			for (int j = i - 1; j > 0; --j) {
				space_left -= words[j - 1];
				if (space_left < 0) {
					break;
				}
				DP[i] = min(DP[i], DP[j - 1] + static_cast<int>(pow(space_left, 2)));
				--space_left;
			}
		}
		return DP[n - 1];
	}
};

int main() {
	Solution s;
	string test1 = "www bb cc fffff";
	s.minimumRaggedness(test1, 6);
}