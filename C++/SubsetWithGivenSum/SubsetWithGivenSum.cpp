#include <vector>
#include <algorithm>

using namespace std;

/* This puzzle is basically to find a subset inside an array with sum equal to given sum.
* If we just want to know whether there is subset, we can solve this problem easily with Dynamic Programming.
* However, we want the specific answer here, so what I am doing is basically listing all the possible subsets.
* It is an O(2 ^ n) solution. With our n = 26, it is extremely time consuming, and it is 'unsolvable' by my computer.
* So in my recursive findSubsetHelper function, we have to do branch pruning to cut off unnecessary calculations.
* I check whether my current sum is larger than the target, if it is, I would just return. However, with my simple pruning logic,
* it is still ‘unsolvable’ by my computer. I could not come up a better pruning method.
* Then I calculate the sum of the given numbers and find out that it is close to 100,000,000.
* So instead of find subset with sum equal to 100,000,000, I would find a subset with sum equal to 29,161,818.
* Subtracting this subset from the original array, we will get the answer we want.
* The given sample has a lot similar and small data(for ex. 2149217 and 2134508), it makes my pruning logic very ineffective.
* Changing the target number to a smaller number makes the computer doing less calculations before making the pruning.
* As a result, even with the same size input, my personal PC can finish running my code within few seconds.
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
	for (int i = 0; i < 26; ++i) {
		sum += areas[i];
	}
	unsigned long overValue = sum - expectedSum;
	printf("sum is %d\n", sum);
	printf("average is %d\n", sum / 26);
	printf("overValue is %d\n", overValue);

	//subtarct the largert two elements because their sum is 31,725,946 which is larger than the
	//over value that is 29,161,818
	vector<unsigned long> subAreas(areas.begin(), areas.end() - 2);
	vector<unsigned long> numsToBeSubtracted = findSubset(subAreas, overValue);
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