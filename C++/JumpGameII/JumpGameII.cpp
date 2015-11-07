#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;

int jump(vector<int> A) {
	// wirte your code here

	/*int index = A.size() - 1;
	int step = 1;
	for (int i = A.size() - 2; i >= 0; i--) {
	if (i + A[i] < index) {
	++step;
	index = i + 1;
	}
	}*/
	vector<int> step(A.size(), INT_MAX);

	step[0] = 0;

	for (int i = 1; i < A.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (step[j] != INT_MAX && j + A[j] >= i) {
				step[i] = min(step[i], step[j] + 1);
			}
		}
	}

	return step[A.size() - 1];
}

int main() {

	vector<int> A;

	A.push_back(13);
	A.push_back(52);
	A.push_back(42);
	A.push_back(21);
	A.push_back(58);

	cout << jump(A) << endl;

	return 0;
}