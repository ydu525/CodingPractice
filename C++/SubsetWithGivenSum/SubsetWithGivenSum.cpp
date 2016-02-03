#include <vector>
#include <algorithm>

using namespace std;

/*
* Thoughts on solving the puzzle:
*
* This puzzle is equivalent to find a subset of an array with sum equal to given sum.
* If we just want to know whether there is such a subset, we can solve this problem easily with Dynamic Programming.
* However, we want the specific answer here, so I think the best-known algorithm is calculating all possible subsets.
* It is an O(2 ^ n) solution. With our input n = 26, it is extremely time-consuming, and my computer could not finish the code execution within a considerable time.
* So inside the recursive findSubsetHelper function, we have to do branch pruning to cut off unnecessary calculations.
* I check whether my accumulated sum is larger than the target, if it is, I would stop further calculation.
* However, this simple pruning logic does not improve the run time significantly.
* Then I did some observation and found out that the sum of the given numbers is close to 100,000,000.
* So instead of to find subset with sum equal to 100,000,000, I would try to find the complementary subset.
* Subtracting the complementary subset from the original array, we will get the answer we want.
* The given sample has many similar and "small" data(compared to our target sum, for ex. 2149217 and 2134508).
* Subtracting the largest two elements from the array, rest of the array (24 nums) would only sum up to 97,435,872 which is less than 100,000,000.
* So the pruning condition would not be triggered during most of the calculations.
* Changing the target sum to a smaller number by finding the complementary subset makes the pruning logic become more effective.
* As a result, even with the same size input, my personal PC could finish running the code within few seconds.
*
* The answer is
* 	18897109, 12828837, 9461105, 6371773, 5946800, 5582170,
* 	5268860, 4552402, 4335391, 4296250, 4224851, 3279833,
* 	3095313, 2812896, 2543482, 2226009, 2142508, 2134411
*/

bool findSubsetHelper(size_t index, vector<unsigned long> &res, unsigned long curSum, vector<unsigned long> &nums, unsigned long expectedSum) {
	if (curSum == expectedSum) {
		return true;
	}

	for (size_t i = index; i < nums.size(); ++i) {
		if ((curSum + nums[i]) > expectedSum) {
			return false;
		}

		res.push_back(nums[i]);
		if (findSubsetHelper(i + 1, res, curSum + nums[i], nums, expectedSum)) {
			return true;
		}
		else {
			res.pop_back();
		}
	}

	return false;
}

vector<unsigned long> findSubset(vector<unsigned long> nums, unsigned long expectedSum) {
	vector<unsigned long> res;

	findSubsetHelper(0, res, 0, nums, expectedSum);

	return res;
}

int main() {
	const unsigned long expectedSum = 100000000;
	vector<unsigned long> areas = { 18897109, 12828837, 9461105,
		6371773, 5965343, 5946800, 5582170, 5564635, 5268860,
		4552402, 4335391, 4296250, 4224851, 4192887, 3439809,
		3279833, 3095313, 2812896, 2783243, 2710489, 2543482,
		2356285, 2226009, 2149127, 2142508, 2134411 };

	//sort the array, so we can skip some branch that is already larger than the pass in number
	sort(areas.begin(), areas.end());

	//just some obervation codes here
	unsigned long sum = 0;
	for (size_t i = 0; i < areas.size(); ++i) {
		sum += areas[i];
	}
	unsigned long overValue = sum - expectedSum;
	printf("sum is %d\n", sum);
	printf("average is %d\n", sum / (unsigned long)areas.size());
	printf("overValue is %d\n", overValue);

	vector<unsigned long> numsToBeSubtracted = findSubset(areas, overValue);
	vector<unsigned long> res;
	for (size_t i = 0, j = 0; i < areas.size(); ++i) {
		if (j >= numsToBeSubtracted.size() || areas[i] != numsToBeSubtracted[j]) {
			res.push_back(areas[i]);
		}
		else {
			++j;
		}
	}

	//check result
	sum = 0;
	for (size_t i = 0; i < res.size(); ++i) {
		sum += res[i];
	}
	if (sum == expectedSum) {
		printf("found subset!\n");
	}
	else {
		printf("not found subset!\n");
	}

	return 0;
}