#include <vector>
#include <algorithm>
#include <list>

using namespace std;

class Solution {
public:
	void help(vector<int>& nums, vector<int>& vec, vector<int>& copy, int l, int r, vector<int>& smaller) {

		if (l == r) return;

		int m = l + (r - l) / 2;
		help(nums, vec, copy, l, m, smaller);
		help(nums, vec, copy, m + 1, r, smaller);

		int i = l, j = m + 1, k = l;
		while (i <= m || j <= r) {
			if (j == r + 1 || (i <= m &&  nums[vec[i]] <= nums[vec[j]])) {
				copy[k++] = vec[i];
				smaller[vec[i]] += j - m - 1;
				i++;
			}
			else copy[k++] = vec[j++];
		}

		for (int i = l; i <= r; i++) {
			vec[i] = copy[i];
		}
	}

	vector<int> countSmallerV2(vector<int>& nums) {
		vector<int> res;
		if (nums.empty()) return res;

		vector<int> vec, copy;
		for (int i = 0; i < nums.size(); i++) {
			vec.push_back(i);
			copy.push_back(i);
		}


		vector<int> smaller(nums.size(), 0);

		help(nums, vec, copy, 0, vec.size() - 1, smaller);

		for (int i : smaller) {
			res.push_back(i);
		}

		return res;
	}

	vector<int> countSmaller(vector<int>& nums) {
		int n = nums.size();
		vector<int> res;
		vector<pair<int, int>> copy;
		vector<int> ht(nums.size(), 0); //index - count of smaller number
		list<int> l;
		vector<list<int>::iterator> idx_ht(nums.size(), l.end());
		for (int i = 0; i < n; ++i) {
			idx_ht[i] = l.insert(l.end(), i);
			l.emplace_back(-1);
		}
		for (int i = 0; i < n; ++i) {
			copy.emplace_back(nums[i], i);
		}
		mergeSort(copy.begin(), copy.end(), SortComp(ht, l, idx_ht));
		for (auto& r : ht) {
			res.push_back(r);
		}
		return res;
	}
private:
	class SortComp {
		vector<int>& ht_;
		list<int>& l_;
		vector<list<int>::iterator>& idx_ht_;
	public:
		SortComp(vector<int>& ht, list<int>& l, vector<list<int>::iterator>& idx_ht) : ht_(ht), l_(l), idx_ht_(idx_ht){}
		bool operator() (const pair<int, int>& rhs, const pair<int, int>& lhs) const {
			if (rhs.first < lhs.first) {
				auto lhs_it = idx_ht_[lhs.second];
				auto rhs_it = idx_ht_[rhs.second];
				l_.erase(idx_ht_[rhs.second]);
				idx_ht_[rhs.second] = l_.insert(lhs_it, rhs.second);
				for (auto it = idx_ht_[lhs.second]; it != l_.end() && *it != -1; ++it) {
					++ht_[*it];
				}
				return true;
			}
			auto lhs_it = idx_ht_[lhs.second];
			if (*(++lhs_it) == -1) {
				l_.erase(lhs_it);
			}
			return false;
		}
	};

	template<typename It, class C>
	std::vector<typename It::value_type> merge(const It begin, const It mid, const It end, C& comp)
	{
		std::vector<typename It::value_type> v;
		It it_l{ begin }, it_r{ mid };
		const It it_mid{ mid }, it_end{ end };

		while (it_l != it_mid && it_r != it_end)
		{
			v.push_back((comp(*it_r, *it_l)) ? *it_r++ : *it_l++);
		}

		v.insert(v.end(), it_l, it_mid);
		v.insert(v.end(), it_r, it_end);

		return std::move(v);
	}

	template<typename It, class C>
	void mergeSort(It begin, It end, C& comp)
	{
		auto size = std::distance(begin, end);
		if (size < 2)
			return;

		auto mid = std::next(begin, size / 2);
		mergeSort(begin, mid, comp);
		mergeSort(mid, end, comp);

		auto &&v = merge(begin, mid, end, comp);
		std::move(v.cbegin(), v.cend(), begin);
	}

	/*void merge(vector<pair<int, int>>::iterator l, vector<pair<int, int>>::iterator m,
		vector<pair<int, int>>::iterator r, SortComp& comp) {
		vector<pair<int, int>>::iterator i, j, k;

		vector<pair<int, int>> L(l, m + 1);
		vector<pair<int, int>> R(m + 1, r);
		int n1 = L.size();
		int n2 = R.size();

		// Merge the temp arrays back into arr[l..r]
		i = L.begin(); // Initial index of first subarray
		j = R.begin(); // Initial index of second subarray
		k = l; // Initial index of merged subarray
		while (i != L.end() && j != R.end()) {
			if (comp(*j, *i))
			{
				*k = *j;
				++j;
			}
			else
			{
				*k = *i;
				++i;
			}
			++k;
		}

		while (i != L.end()) {
			*k = *i;
			++i;
			++k;
		}

		while (j != R.end()) {
			*k = *j;
			++j;
			++k;
		}
	}

	void mergeSort(vector<pair<int, int>>::iterator first, vector<pair<int, int>>::iterator last,
		SortComp& comp) {
		if (first < last)
		{
			// Same as (l+r)/2, but avoids overflow for
			// large l and h
			auto mid = first + (last - first) / 2;

			// Sort first and second halves
			mergeSort(first, mid, comp);
			mergeSort(mid, last, comp);

			merge(first, mid, last, comp);
		}
	};*/
};

int main() {
	Solution s;
	vector<int> test1 = { 5, 2, 6, 1};
	vector<int> test2 = { 5, 2, 6, 1, 11, 22, 7, 3, 4, 1, 16 };

	s.countSmaller(test1);
	s.countSmaller(test2);
}