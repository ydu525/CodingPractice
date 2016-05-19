/*
 * if a student be late (L) 3 days in a row, he will fail the class.
 * if a student be absent (A) any 2 days, he will fail the class.
 * Given n days, what is number of combinations a student can have for his attendency record without failing the class
 */

#include <vector>
#include <iostream>

using namespace std;
 
// please refer to the attached picture for the automata states
int findGoodComb(int n) {
    vector<vector<int>> f(n + 1, vector<int>(6, 0));
    
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
    	f[i][0] = f[i - 1][0] + f[i - 1][1] + f[i - 1][2];
    	f[i][1] = f[i - 1][0];
    	f[i][2] = f[i - 1][1];
    	f[i][3] = f[i - 1][0] + f[i - 1][1] + f[i - 1][2] + f[i - 1][4] + f[i - 1][5];
    	f[i][4] = f[i - 1][3];
    	f[i][5] = f[i - 1][4];
    }
    
    int res = 0;
    for (int i = 0; i < 6; ++i) {
        res += f[n][i];
    }
	
    return res;
}

int main() {
	cout << findGoodComb(1) << endl;
}