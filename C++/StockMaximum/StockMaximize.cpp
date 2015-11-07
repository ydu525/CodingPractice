#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//0, 0, 0, 0

void findTradeResults(int &res, int i, int shares, int profit, const vector<int> &p) {

	if (i == p.size()) {
		return;
	}

	if (shares > 0) {
		//sell any number
		for (int k = 1; k <= shares; k++) {
			int tmp = shares * p[i] + profit;
			res = max(res, tmp);
			findTradeResults(res, i + 1, shares - k, tmp, p);
		}
	}
	//do nothing
	findTradeResults(res, i + 1, shares, profit, p);
	//buy 1 share
	findTradeResults(res, i + 1, ++shares, profit - p[i], p);

	return;
}

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */

	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		vector<int> p; //predictions;    
		int res = 0;
		int N;

		cin >> N;

		for (int j = 0; j < N; j++) {
			int tmp;
			cin >> tmp;
			p.push_back(tmp);
		}

		findTradeResults(res, 0, 0, 0, p);
		cout << res << endl;
	}

	return 0;
}
