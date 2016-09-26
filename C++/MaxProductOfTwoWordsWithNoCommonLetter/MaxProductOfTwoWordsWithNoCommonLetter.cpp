#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
	unsigned int maxProduct(const vector<string>& dict) {
		unsigned int res = 0;
		if (dict.empty()) {
			return res;
		}
		if (dict.size() == 1) {
			return (int) dict[0].size();
		}
		auto bit_sets = wordsToBitSets(dict);
		const unsigned int used_mask = 0x3FFFFFF;
		for (const auto& word : dict) {
			auto index = wordToIndex(word);
			unsigned index_c = (~index) & used_mask;
			res = max(res, bit_sets[index] * bit_sets[index_c]);
		}
		return res;
	}
private:
	unsigned int wordToIndex(const string& word) {
		unsigned int index = 0;
		for (const auto& c : word) {
			index |= 1 << (c - 'a');
		}
		return index;
	}
	vector<unsigned int> wordsToBitSets(const vector<string>& dict) {
		const unsigned int s = static_cast<unsigned int>(pow(2, 26));
		vector<unsigned int> bit_sets(s, 0);
		//insert all words into the bit sets
		for (const auto& word : dict) {
			unsigned int index = wordToIndex(word);
			bit_sets[index] = max(bit_sets[index], word.size());
		}
		//use DP to process the bit sets, such that each cell will contain 
		//the length of the longest word that consists of exactly those letters
		//or the length of the longest word that consists of at most those letters
		const unsigned int bit_mask = 0xFFFFFFFF;
		for (unsigned int i = 1; i < s; ++i) {
			for (unsigned int j = 0; j < 26; ++j) {
				unsigned int pre = i & (bit_mask & ~(1 << j));
				if (pre == 0) {
					break;
				}
				bit_sets[i] = max(bit_sets[i], bit_sets[pre]);
			}
		}
		return bit_sets;
	}
};

int main() {
	vector<string> test1 = { "aaaaaa", "a", "abb", "bbbbbbbbbbbbbbbbbbbbbb", "ca" };
	vector<string> test2 = { "boy", "boat", "cat", "zxy" };
	Solution s;
	s.maxProduct(test1);
}