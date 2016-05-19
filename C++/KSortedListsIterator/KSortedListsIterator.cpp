/*
 * implement a iterator class for k sorted lists
 */
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class KSortedLists{
public:

	KSortedLists(const vector<vector<int>>& lists) : l_(lists) {}
	
	class iterator {
	public:
	
		friend class KSortedLists;
		
		iterator(vector<vector<int>>& lists) {
			for (auto& l : lists) {
				q_.emplace(l.begin(), l.end());
			}
		}
		
		//pre
		iterator& operator++() {
			auto n = q_.top();
			q_.pop();
			++(n.first);
			if (n.first != n.second) {
				q_.push(move(n));
			}
			return *this;
		}
		//post
		iterator operator++(int) {
			iterator tmp(*this); 
			operator++(); 
			return tmp;
		}

		int& operator*() {
			return *(q_.top().first);
		}
		
	private:
	
		using node = pair<vector<int>::iterator, vector<int>::iterator>;
		
		class mycomparison
        {
        public: 
          bool operator() (const node& lhs, const node& rhs) const
          {
             return *(lhs.first) > *(rhs.first);
          }
        };
        
		priority_queue<node, vector<node>, mycomparison> q_;
	};
	
	iterator begin() {
	    return iterator(l_);
	}

	iterator end() {
		return iterator(vector<vector<int>>());
	}
	
private:

	vector<vector<int>> l_;
};

int main()
{
  vector<vector<int>> lists = {{1, 6, 7, 9}, {2, 5, 8, 10}};
  KSortedLists klists(lists);
  auto it = klists.begin();
  cout << *it << endl;
  ++it;
  cout << *it++ << endl;
  cout << *it << endl;
  cout << *++it << endl;
  cout << *++it << endl;
  cout << *++it << endl;
  cout << *++it << endl;
  cout << *++it << endl;
}
