/*
* see http://www.lintcode.com/en/problem/consistent-hashing-ii/ for problem description
*/

#include <vector>
#include <map>
#include <unordered_map>
#include <random>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class Solution {
public:
	// @param n a positive integer
	// @param k a positive integer
	// @return a Solution object
	static Solution create(int n, int k) {
		// Write your code here
		srand(time(NULL));
		Solution ret;
		ret.n_ = n;
		ret.k_ = k;
		ret.pGenerator_ = new default_random_engine(random_device{}());
		ret.pDistribution_ = new uniform_int_distribution<int>(0, n - 1);
		return ret;
	}

	// @param machine_id an integer
	// @return a list of shard ids
	vector<int> addMachine(int machine_id) {
		// Write your code here
		auto it = id_to_point_.find(machine_id);
		if (it != id_to_point_.end()) {
			return it->second;
		} else {
			id_to_point_.emplace(machine_id, vector<int>());
			int point;
			for (int i = 0; i < k_; ++i) {				
				while (1) {
					point = rand() % n_;//(*pDistribution_)(*pGenerator_);
					if (point_to_id_.find(point) == point_to_id_.end()) {
						point_to_id_.emplace(point, machine_id);
						id_to_point_[machine_id].push_back(point);
						break;
					}
				}
			}
			sort(id_to_point_[machine_id].begin(), id_to_point_[machine_id].end());
			return id_to_point_[machine_id];
		}
	}

	// @param hashcode an integer
	// @return a machine id
	int getMachineIdByHashCode(int hashcode) {
		// Write your code here
		auto it = point_to_id_.find(hashcode);
		if (it == point_to_id_.end()) {
			it = point_to_id_.upper_bound(hashcode);
			if (it == point_to_id_.end()) {
				it = point_to_id_.begin();
			}
		}
		return it->second;
	}

	~Solution() {
		delete pGenerator_;
		delete pDistribution_;
	}

private:
	unordered_map<int, vector<int>> id_to_point_;
	map<int, int> point_to_id_;
	int n_;
	int k_;
	default_random_engine *pGenerator_;
	uniform_int_distribution<int> *pDistribution_;
};

int main() {
	Solution s1 = Solution::create(100, 3);
	vector<int> points = s1.addMachine(1);
	points = s1.addMachine(2);
	int id = s1.getMachineIdByHashCode(99);
	id = s1.getMachineIdByHashCode(55);
}