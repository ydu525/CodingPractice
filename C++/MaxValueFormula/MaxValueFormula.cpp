#include <vector>
#include <algorithm>
#include <list>
#include <string> 

using namespace std;

class Solution {
public:
	double maxValue(const vector<double>& nums) {
		int s = nums.size();
		if (s == 0) {
			return 0;
		}
		dp_ = vector<vector<double>>(s, vector<double>(s, -numeric_limits<double>::max()));

		for (int i = 0; i < s; ++i) {
			dp_[i][i] = nums[i];
		}

		for (int i = 1; i < s; ++i) {
			for (int j = i - 1; j >= 0; --j) {
				for (int k = j; k < i; ++k) {
					dp_[j][i] = max(dp_[j][i], max(dp_[j][k] + dp_[k + 1][i], dp_[j][k] * dp_[k + 1][i]));
				}
			}
		}

		return dp_[0][s - 1];
	}

	string maxValueFormula(const vector<double>& nums) {
		string res = "";
		int s = nums.size();
		if (s == 0) {
			return res;
		}
		maxValue(nums);
		list<string> res_list;
		
		maxValueFormulaHelper(nums, 0, s - 1, res_list, res_list.begin(), res_list.begin(), "+");
		for (auto it = res_list.begin(); it != res_list.end(); ++it) {
			res.append(*it);
		}
		return res;
	}
private:
	void maxValueFormulaHelper(const vector<double>& nums, int start_i, int end_i, list<string>& res_list, list<string>::iterator list_b, list<string>::iterator list_e, string last_op) {
		if (start_i == end_i) {
			res_list.insert(list_b, to_string(nums[start_i]));
			return;
		}
		auto next_b = list_b;
		auto next_e = list_e;
		for (int k = start_i; k < end_i; ++k) {
			if ((dp_[start_i][k] + dp_[k + 1][end_i]) == dp_[start_i][end_i]) {
				next_b = res_list.insert(list_b, "+");
				if (last_op != "+") {
					res_list.insert(next_b, "(");
					next_e = res_list.insert(list_e, ")");
				}
				maxValueFormulaHelper(nums, start_i, k, res_list, next_b, next_b, "+");
				maxValueFormulaHelper(nums, k + 1, end_i, res_list, next_e, next_e, "+");
				break;
			}
			else if ((dp_[start_i][k] * dp_[k + 1][end_i]) == dp_[start_i][end_i]) {
				next_b = res_list.insert(list_b, "*");
				maxValueFormulaHelper(nums, start_i, k, res_list, next_b, next_b, "*");
				maxValueFormulaHelper(nums, k + 1, end_i, res_list, next_e, next_e, "*");
				break;
			}
		}
	}

	vector<vector<double>> dp_;
};

int main() {
	Solution s;
	vector<double> test1 = { 0, -1, 4, -9, 0.5 };
	s.maxValueFormula(test1);
}

