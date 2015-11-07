#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//After we sort the input array, there are three scenarios
//1: {2, 2, 2, 2}, we have to buy them all, total cost is 8
//2: {2, 2, 3, 4}, 2&4 is a pair, 2&3 is a pair, total cost is 7
//3: {1, 2, 3, 4}, 1&2 is a pair, 3&4 is a pair, total cost is 6
int minimumCost(vector<int>& prices) {

	if (prices.empty()) {
		return 0;
	}

	sort(prices.begin(), prices.end());

	int i, j, k;
	int num = prices.size();
	vector<vector<int>> f(num, vector<int>(num, 0));

	for (j = 0; j < num; ++j) {
		for (i = 0; i <= j; ++i) {

			//if all the prices in i to j region are equal
			//we have to buy them all
			if (prices[i] == prices[j]) {
				f[i][j] = prices[j] * (j - i + 1);
				continue;
			}

			//in the region i to j, buying j will give us i for free
			//the total cost would be price j
			//plus the cost of buying i + 1 to j - 1
			//since we init our f[][] to be all 0s
			//plus something like f[3][2] will just add 0 to the cost
			f[i][j] = f[i + 1][j - 1] + prices[j];
		}
	}

	//we computed scenarios 1 & 2
	//have to compare them with scenario 3
	for (j = 0; j < num; ++j) {
		for (i = 0; i < j; ++i) {
			for (k = i; k < j; ++k) {
				f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
			}
		}
	}

	return f[0][num - 1];
}

int main()
{
	vector<int> test0;
	int ins1[] = { 4, 7, 8 };
	vector<int> test1(ins1, ins1 + sizeof(ins1) / sizeof(int));
	int ins2[] = { 1, 2, 3, 4 };
	vector<int> test2(ins2, ins2 + sizeof(ins2) / sizeof(int));
	int ins3[] = { 2, 2, 3, 4 };
	vector<int> test3(ins3, ins3 + sizeof(ins3) / sizeof(int));
	int ins4[] = { 2, 2, 2, 4 };
	vector<int> test4(ins4, ins4 + sizeof(ins4) / sizeof(int));
	int ins5[] = { 2, 2, 2, 2 };
	vector<int> test5(ins5, ins5 + sizeof(ins5) / sizeof(int));

	if (minimumCost(test0) != 0) {
		cout << "test0 failed!" << endl;
	}
	cout << "test0 passed!" << endl;
	if (minimumCost(test1) != 12) {
		cout << "test1 failed!" << endl;
	}
	cout << "test1 passed!" << endl;
	if (minimumCost(test2) != 6) {
		cout << "test2 failed!" << endl;
	}
	cout << "test2 passed!" << endl;
	if (minimumCost(test3) != 7) {
		cout << "test3 failed!" << endl;
	}
	cout << "test3 passed!" << endl;
	if (minimumCost(test4) != 8) {
		cout << "test4 failed!" << endl;
	}
	cout << "test4 passed!" << endl;
	if (minimumCost(test5) != 8) {
		cout << "test5 failed!" << endl;
	}
	cout << "test5 passed!" << endl;

	return 0;
}