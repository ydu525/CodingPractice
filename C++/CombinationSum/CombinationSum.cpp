#include <vector>
#include <algorithm>

using namespace std;

void combinationSumHelper(const vector<int> &candidates,
	int target, vector<vector<int> >& res, vector<int>& cur, int sum, int index) {

	for (int i = index; i < candidates.size(); ++i) {
		if (i > 0 && candidates[i] == candidates[i - 1]) {
			continue;
		}

		if (candidates[i] + sum == target) {
			cur.push_back(candidates[i]);
			res.push_back(cur);
			cur.pop_back();
			return;
		}
		else if (candidates[i] + sum < target) {
			sum += candidates[i];
			cur.push_back(candidates[i]);
			combinationSumHelper(candidates, target, res, cur, sum, i);
			combinationSumHelper(candidates, target, res, cur, sum, i + 1);
			cur.pop_back();
			sum -= candidates[i];
		}
		else {
			return;
		}
	}

	return;
}

vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
	// write your code here
	if (candidates.empty()) {
		return{};
	}

	sort(candidates.begin(), candidates.end());

	vector<vector<int> > res;
	vector<int> cur;

	combinationSumHelper(candidates, target, res, cur, 0, 0);

	return res;
}

int main() {
	vector<int> candidates;

	candidates.push_back(2);
	candidates.push_back(3);
	candidates.push_back(5);

	combinationSum(candidates, 7);

	return 0;
}