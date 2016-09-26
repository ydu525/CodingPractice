#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct city {
	int id;
	string name;
	vector<int> dst_cities;
	vector<int> holidays;
	city(int i, const string& n) : id(i), name(n) {
		holidays.resize(12);
	}
};

int maxHolidays(const vector<city>& cities) {
	int n = cities.size();
	int res = 0;
	if (n == 0) {
		return res;
	}
	unordered_map<int, int> lookup;
	vector<vector<int>> dp(13, vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		lookup.emplace(cities[i].id, i);
	}
	for (int i = 1; i <= 12; ++i) {
		for (int j = 0; j < n; ++j) {
			dp[i][j] = max(dp[i][j], dp[i - 1][j]);
			for (const auto& id : cities[j].dst_cities) {
				dp[i][j] = max(dp[i][j], dp[i - 1][lookup[id]]);
			}
			dp[i][j] += cities[j].holidays[i - 1];
		}
	}
	for (int num : dp[12]) {
		res = max(res, num);
	}
	return res;
}

struct cityV2 {
	int id;
	string name;
	vector<cityV2*> dst_cities;
	vector<int> holidays;
};

struct myHash {
	inline std::size_t operator()(const std::pair<int, int>& p) const {
		return (hash<int>()(p.first) + hash<int>()(p.second));
	}
};

using t_hash = unordered_map<pair<int, int>, int, myHash>;

int maxHolidaysV2Helper(cityV2* city, int& month, t_hash& lookup) {
	auto p = make_pair(month, city->id);
	auto it = lookup.find(p);
	if (it != lookup.end()) {
		return it->second;
	}
	int max_holidays = 0;
	++month;
	for (auto& dst : city->dst_cities) {
		max_holidays = max(max_holidays, maxHolidaysV2Helper(dst, month, lookup));
	}
	max_holidays += city->holidays[--month];
	lookup[p] = max_holidays;
	return max_holidays;
}

int maxHolidaysV2(cityV2* start_c) {
	t_hash lookup; //key: <month, city_id>, value: max holidays
	int month = 1;
	return maxHolidaysV2Helper(start_c, month, lookup);
}

int main() {
	city c1(57, "c1");
	city c2(77, "c2");
	city c3(89, "c3");
	city c4(100, "c4");
	c1.dst_cities = { 77, 89 };
	c2.dst_cities = { 57 };
	c3.dst_cities = { 57, 100 };
	c4.dst_cities = { 89 };
	c1.holidays = { 1, 7, 8, 4, 6, 10, 3, 2, 1, 12, 0, 7 };
	c2.holidays = { 1, 7, 8, 4, 6, 10, 3, 2, 1, 12, 0, 7 };
	c3.holidays = { 1, 7, 8, 4, 6, 10, 3, 2, 1, 12, 0, 7 };
	c4.holidays = { 1, 7, 8, 4, 6, 10, 3, 2, 1, 12, 0, 7 };
	vector<city> test1 = { c1, c2, c3, c4 };
	maxHolidays(test1);
}