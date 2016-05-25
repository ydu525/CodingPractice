#include <vector>
#include <queue>
#include <utility>

using namespace std;

class Solution {
public:
	vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
		priority_queue<node, vector<node>, nodeComp> pq;
		vector<pair<int, int>> res;
		for (auto& b : buildings) {
			node n(b[0], b[1], b[2]);
			while (!pq.empty() && n.li > pq.top().ri) {
				popEnds(pq, res);
			}
			if (pq.empty() || n.height > pq.top().height) {
				res.emplace_back(n.li, n.height);
			}
			pq.push(n);
		}
		while (!pq.empty()) {
			popEnds(pq, res);
		}
		return res;
	}
private:
	class node {
	public:
		int li;
		int ri;
		int height;
		node(int l, int r, int h) : li(l), ri(r), height(h) {}
	};
	struct nodeComp {
		bool operator() (const node& n1, const node& n2) const {
			return n1.height < n2.height;
		}
	};
	void popEnds(priority_queue<node, vector<node>, nodeComp> &pq, vector<pair<int, int>> &res) {
		node pre = pq.top();
		pq.pop();
		while (pre.ri > pq.top().ri) {
			pq.pop();
		}
		if (!pq.empty()) {
			res.emplace_back(pre.ri, pq.top().height);
		}
		else {
			res.emplace_back(pre.ri, 0);
		}
	}
};

int main() {
	vector<vector<int>> test1 = { { 2, 13, 10 }, { 10, 17, 25 }, { 12, 20, 14 } };
	Solution s;
	s.getSkyline(test1);
}