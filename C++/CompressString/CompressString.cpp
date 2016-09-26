#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
	string compressString(const string& in) {
		string res1 = "";
		string res2 = "";
		if (in.empty()) {
			return res1;
		}
		unordered_map<string, string> record;
		res1 = compressStringHelper(in, record);
		do {
			res2 = res1;
			res1 = compressStringHelper(res2, record);
		} while (res2.size() != res1.size());
		return res1;
	}

	string compressStringHelper(string in, unordered_map<string, string>& record) {	
		if (in.empty()) {
			return "";
		}
		auto it = record.find(in);
		if (it != record.end()) {
			return it->second;
		}
		const int s = in.size();
		string res;
		res = in[0] + compressStringHelper(in.substr(1), record);
		for (int i = 1; i < s; ++i) {
			string tmp_r = compressStringHelper(in.substr(i + 1), record);
			int w_size = 1;
			string tmp_l = in.substr(0, i + 1);
			for (int w_size = 1; w_size <= (i + 1) / 2; ++w_size) {
				string tmp = encode(in.substr(0, i + 1), w_size);
				if (tmp.size() < tmp_l.size()) {
					tmp_l = tmp;
				}
			}
			if (res.size() > tmp_l.size() + tmp_r.size()) {
				res = tmp_l + tmp_r;
			}
		}
		record.emplace(move(in), res);
		return res;
	}

	string encode(string src, int w_size)
	{
		int rLen;
		string res;
		const int len = src.size();

		for (int i = 0; i < len; i += w_size)
		{
			string c = src.substr(i, w_size);

			rLen = 1;
			while (i + w_size < len && compare(src, i, i + w_size, w_size))
			{
				rLen++;
				i += w_size;
			}

			if (rLen == 1) {
				res += c;
			}
			else {		
				if (w_size == 1) {
					res += c;
				}
				else {
					res += '[' + c + ']';
				}
				if (rLen != w_size) {
					res += to_string(rLen);
				}
			}
		}

		return res;
	}

	bool compare(const string& src, int l, int r, int w_size) {
		bool contain_letter = false;
		for (int i = 0; i < w_size; ++i) {
			if (isalpha(src[l + i])) {
				contain_letter = true;
			}
			if (src[l + i] != src[r + i]) {
				return false;
			}
		}
		if (contain_letter)
			return true;

		return false;
	}
};

int main() {
	Solution s;
	string res;
	s.encode("aaaabbbccccc", 1);
	s.encode("abababcdcd", 2);
	s.encode("abcabc", 2);
	s.encode("abcabc", 3);
	s.encode("abcabcabc", 3);
	s.encode("aaabcabcbcab", 3);
	s.encode("222222222222", 1);
	s.encode("[[[[[[[[[[[[[[[", 1);
	res = s.compressString("aaaabab");
	res = s.compressString("aaaabcabcbcabc");
	res = s.compressString("aaabaaabccccdaaabaaabccccd");
	return 0;
}