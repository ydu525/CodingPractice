/*
 * Given an array. Check whether 2 power the minimum of the array is larger then the maximum of the array.
 * follow up 1: (minTakesFront)     If you can take out the front elements in the array, how many steps it takes to make the rest of the array satisfying the above condition?
 * follow up 2: (minTakesBothEnds)  what if you can take out elements from both ends of the arrary? Then what is the minimum steps to find a subarray that satisfying the above condition?
 */
 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

bool checkPow(const int& minValue, const int& maxValue) {
    errno = 0;
    double pow2 = std::pow( minValue, 2 );
    if ( errno == 0 ) {
        //  std::pow succeeded (without overflow)
        if (pow2 > maxValue) {
            return true;
        }
    } else {
        //  some error (probably overflow) with std::pow.
        return false;
    }   
    return false;
}

int minTakesFront(const vector<int>& nums) {
	int minValue = numeric_limits<int>::max();
	int maxValue = numeric_limits<int>::min();
	int s = static_cast<int>(nums.size());
	int i = s - 1;
	for (; i >= 0 ; --i) {    
		minValue = min(nums[i], minValue);
		maxValue = max(nums[i], maxValue);
		if (!checkPow(minValue, maxValue)) {
			break;
		}
	}
	if (i == s - 1) {
		return -1;
	}
	return i + 1;
}

// return minimum steps to make a subarray inside the passed in array such that 2 power the minimum is larger the maximum 
// or -1 if there is no such subarray
int minTakesBothEnds(const vector<int>& nums) {
	int s = static_cast<int>(nums.size());
	
	if (s == 0) {
	    return -1;
	}
	
	vector<vector<int>> f(s, vector<int>(s, 0));
	for (int i = 0; i < s; ++i) {
	    if (checkPow(nums[i], nums[i])) {
	        f[i][i] = 0;
	    } else {
	        f[i][i] = 1;
	    }
	}
	
	for (int i = s - 1; i >= 0; --i) {
		int minValue = nums[i];
		int maxValue = nums[i];
		for (int j = i + 1; j < s; ++j) {
			minValue = min(nums[j], minValue);
			maxValue = max(nums[j], maxValue);
			if (checkPow(minValue, maxValue)) {
				f[i][j] = 0;
			} else {
				f[i][j] = min(f[i + 1][j], f[i][j - 1]) + 1;
			}
		}
	}
	
	//if steps equal to size of the array, all elements have been taken out
	if (f[0][s - 1] == s) {
	    return -1;
	}
	
	return f[0][s - 1];
}

int main()
{
  vector<int> test1 = {5};
  vector<int> test2 = {1};
  vector<int> test3 = {5, 1, 3};
  vector<int> test4 = {1, 1, 1};
  vector<int> test5 = {5, 3, 1};
  vector<int> test6 = {2, 5, 3, 1};
  vector<int> test7 = {-2};
  vector<int> test8 = {1, 5, 3};
  
  cout << "test1 front result : " << minTakesFront(test1) << endl;
  cout << "test2 front result : " << minTakesFront(test2) << endl;
  cout << "test3 front result : " << minTakesFront(test3) << endl;
  cout << "test4 front result : " << minTakesFront(test4) << endl;
  cout << "test5 front result : " << minTakesFront(test5) << endl;
  cout << "test6 front result : " << minTakesFront(test6) << endl;
  cout << "test7 front result : " << minTakesFront(test7) << endl;
  cout << "test8 front result : " << minTakesFront(test8) << endl;
  cout << endl;
  cout << "test1 both result : " << minTakesBothEnds(test1) << endl;
  cout << "test2 both result : " << minTakesBothEnds(test2) << endl;
  cout << "test3 both result : " << minTakesBothEnds(test3) << endl;
  cout << "test4 both result : " << minTakesBothEnds(test4) << endl;
  cout << "test5 both result : " << minTakesBothEnds(test5) << endl;
  cout << "test6 both result : " << minTakesBothEnds(test6) << endl;
  cout << "test7 both result : " << minTakesBothEnds(test7) << endl;
  cout << "test8 both result : " << minTakesBothEnds(test8) << endl;
}
