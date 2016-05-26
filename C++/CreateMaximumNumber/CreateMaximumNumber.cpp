#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
		int s1 = nums1.size();
		int s2 = nums2.size();

		int start1 = 0;
		int start2 = 0;
		int max_num = -1;
		vector<int> res;

		while (k > 0 && k < ((s1 - start1) + (s2 - start2))) {
			int start_t = start1;
			int max1 = -1;
			int max_index1 = -1;
			while (k <= ((s1 - start_t) + (s2 - start2)) && start_t < s1) {
				if (nums1[start_t] > max1) {
					max1 = nums1[start_t];
					max_index1 = start_t;
				}	
				++start_t;
			}

			start_t = start2;
			int max2 = -1;
			int max_index2 = -1;
			while (k <= ((s1 - start1) + (s2 - start_t)) && start_t < s2) {
				if (nums2[start_t] > max2) {
					max2 = nums2[start_t];
					max_index2 = start_t;
				}
				++start_t;
			}

			if (max1 == max2) {
				int pre1 = max_index1 > 0 ? nums1[max_index1 - 1] : -1;
				int pre2 = max_index2 > 0 ? nums2[max_index2 - 1] : -1;
				if (pre1 < pre2) {
					max_num = max1;
					start1 = max_index1 + 1;
				}
				else {
					max_num = max2;
					start2 = max_index2 + 1;
				}
			} else if (max1 > max2){
				max_num = max1;
				start1 = max_index1 + 1;
			}
			else {
				max_num = max2;
				start2 = max_index2 + 1;
			}

			--k;
			res.push_back(max_num);
		}

		while (k > 0) {
			int num = -1;
			if (start1 == s1) {
				num = nums2[start2++];
			}
			else if (start2 == s2) {
				num = nums1[start1++];
			}
			else {
				if (nums1[start1] == nums2[start2]) {
					int next1 = -1;
					int next2 = -1;
					int i = 1;
					while (next1 == next2) {
						if (start1 + i < s1) {
							next1 = nums1[start1 + i];
						}
						else {
							next1 = -1;
						}
						if (start2 + i < s2) {
							next2 = nums2[start2 + i];
						}
						else {
							next2 = -1;
						}
						++i;
					}
					if (next1 > next2) {
						num = nums1[start1];
						++start1;
					}
					else {
						num = nums2[start2];
						++start2;
					}
				}
				else if (nums1[start1] > nums2[start2]) {
					num = nums1[start1];
					++start1;
				}
				else {
					num = nums2[start2];
					++start2;
				}
			}
			--k;
			res.push_back(num);
		}
		return res;
	}
};

int main() {
	Solution s;
	vector<int> test11 = { 3, 9 };
	vector<int> test12 = { 8, 9 };
	vector<int> test21 = { 3, 4, 6, 5 };
	vector<int> test22 = { 9, 1, 2, 5, 8, 3 };
	vector<int> test31 = { 6, 7 };
	vector<int> test32 = { 6, 0, 4 };
	vector<int> test41 = {2, 8, 0, 4, 5, 1, 4, 8, 9, 9, 0, 8, 2, 9};
	vector<int> test42 = {5, 9, 6, 6, 4, 1, 0, 7};
	vector<int> test51 = { 2, 1, 7, 8, 0, 1, 7, 3, 5, 8, 9, 0, 0, 7, 0, 2, 2, 7, 3, 5, 5 };
	vector<int> test52 = { 2, 6, 2, 0, 1, 0, 5, 4, 5, 5, 3, 3, 3, 4 };
	s.maxNumber(test11, test12, 3);
	s.maxNumber(test21, test22, 5);
	s.maxNumber(test31, test32, 5);
	s.maxNumber(test41, test42, 22);
	s.maxNumber(test51, test52, 35);
}