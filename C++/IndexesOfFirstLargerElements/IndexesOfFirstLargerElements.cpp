/*
 * given a array of number, return a array which each element is 
 * the index of the first larger number of each number inside the given array.
 * Assume that if there is no larger number in the right side of a number, use -1 for index. 
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> indexesOfFirstLargerElements(vector<int> nums) {
	if (nums.empty()) {
		return{};
	}
	stack<int> s;
	vector<int> res(nums.size(), -1);
	for (int i = 0; i < (int) nums.size(); ++i) {
		while (!s.empty() && nums[i] > nums[s.top()]) {
			res[s.top()] = i;
			s.pop();
		}
		s.push(i);
	}
	return res;
}

int main()
{
	vector<int> in = { 4, 2, 1, 3, 5 };
	vector<int> res = indexesOfFirstLargerElements(in);
	for (auto &num : res) {
		cout << num;
	}
	cout << endl;
}