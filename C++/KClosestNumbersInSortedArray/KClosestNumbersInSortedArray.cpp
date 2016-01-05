/*
* see http://www.lintcode.com/en/problem/k-closest-numbers-in-sorted-array/ for problem description
*/
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	/**
	* @param A an integer array
	* @param target an integer
	* @param k a non-negative integer
	* @return an integer array
	*/
	vector<int> kClosestNumbers(vector<int>& A, int target, int k) {
		// Write your code here
		vector<int> res;

		if (A.size() == 0 || k <= 0) {
			return res;
		}

		//do binary search to find the element that is closet to target
		int start = 0, end = A.size() - 1, mid;
		int index = -1;

		while (start + 1 < end) {
			mid = start + (end - start) / 2;
			int diff = abs(A[mid] - target);
			int diffL = mid - 1 >= 0 ? abs(A[mid - 1] - target) : INT_MAX;
			int diffR = mid + 1 <= A.size() - 1 ? abs(A[mid + 1] - target) : INT_MAX;
			if (diffL < diff) {
				end = mid;
			}
			else if (diffR < diff) {
				start = mid;
			}
			else {
				index = mid;
				break;
			}
		}

		if (index == -1) {
			if (abs(A[start] - target) < abs(A[end] - target)) {
				index = start;
			}
			else {
				index = end;
			}
		}

		//push k to res
		res.push_back(A[index]);
		start = index - 1;
		end = index + 1;
		--k;
		while (k > 0) {
			if (start < 0 && end > A.size() - 1) {
				break;
			}
			else if (start < 0) {
				res.push_back(A[end++]);
			}
			else if (end > A.size() - 1) {
				res.push_back(A[start--]);
			}
			else {
				if (abs(A[start] - target) <= abs(A[end] - target)) {
					res.push_back(A[start--]);
				}
				else {
					res.push_back(A[end++]);
				}
			}
			--k;
		}

		return res;
	}
};

int main() {
	Solution s;

	vector<int> A = { 1, 2, 3 };
	vector<int> res = s.kClosestNumbers(A, 2, 3);
	A = { 1, 4, 6, 8 };
	res = s.kClosestNumbers(A, 3, 3);

	return 0;
}