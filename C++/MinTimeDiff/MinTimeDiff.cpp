#include <vector>
#include <string>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
	int minTimeDiff(const vector<string>& times) {
		if (times.empty()) {
			return 0;
		}
		int min_diff = numeric_limits<int>::max();
		multiset<myTime, myComp> s(myComp{ min_diff });
		for (const auto& time : times) {
			s.emplace(stoi(time), stoi(time.substr(min_pos)));
			if (min_diff == 0) {
				return min_diff;
			}
		}
		return min_diff;
	}
private:
	const int min_pos = 3;	
	using myTime = pair<int, int>;
	struct myComp {
		const int mph = 60;
		int& min_diff;
		myComp(int& diff) : min_diff(diff) {}
		bool operator() (const myTime& lhs, const myTime& rhs) const
		{
			int diff = (lhs.first - rhs.first) * mph + (lhs.second - rhs.second);
			min_diff = min(min_diff, abs(diff));
			return diff > 0;
		}
	};
};

int main() {
	vector<string> test1 = { "11:01", "5:02", "11:02", "11:01" };
	Solution s;
	s.minTimeDiff(test1);
}