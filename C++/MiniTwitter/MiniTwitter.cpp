/*
* see http://www.lintcode.com/en/problem/mini-twitter/ for problem description
*/

#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <map>
#include <string> 
#include <algorithm>
#include <string>
#include <ctime>
#include <queue>

using namespace std;

class Tweet {
public:
	int id;
	int user_id;
	string text;
	static Tweet create(int user_id, string tweet_text) {
	// This will create a new tweet object,
	// and auto fill id
		static int next_id = 0;
		Tweet tmp;
		tmp.user_id = user_id;
		tmp.text = tweet_text;
		tmp.id = next_id++;
		return tmp;
	}
};

class MiniTwitter {
public:
	MiniTwitter() {
		// initialize your data structure here.
	}

	// @param user_id an integer
	// @param tweet a string
	// return a tweet
	Tweet postTweet(int user_id, string tweet_text) {
		//  Write your code here
		time_t timestamp;
		time(&timestamp);
		Tweet tw = Tweet::create(user_id, tweet_text);
		auto it_db = tweets_db_.find(user_id);
		if (it_db == tweets_db_.end()) {
			map<time_t, Tweet> m;
			m.emplace(timestamp, tw);
			tweets_db_.emplace(user_id, move(m));
		}
		else {
			it_db->second.emplace(++timestamp, tw);
		}
		return tw;
	}

	// @param user_id an integer
	// return a list of 10 new feeds recently
	// and sort by timeline
	vector<Tweet> getNewsFeed(int user_id) {
		// Write your code here
		vector<Tweet> res;	
		priority_queue<QueueNode, vector<QueueNode>, Compare> q;
		auto it_re = ft_relations_.find(user_id);
		if (it_re != ft_relations_.end()) {
			for (const auto &to_user_id : it_re->second) {
				auto it_db = tweets_db_.find(to_user_id);
				if (it_db != tweets_db_.end()) {
					auto it_tw = it_db->second.begin();
					if (it_tw != it_db->second.end()) {
						q.emplace(it_db, it_tw);
					}
				}
			}
		}
		auto it_db = tweets_db_.find(user_id);
		if (it_db != tweets_db_.end()) {
			auto it_tw = it_db->second.begin();
			if (it_tw != it_db->second.end()) {
				q.emplace(it_db, it_tw);
			}
		}
		for (int i = 0; i < feeds_num; ++i) {
			if (q.empty()) {
				break;
			}
			auto node = q.top();
			q.pop();
			res.push_back(node.mIt_tw->second);
			if (++node.mIt_tw != node.mIt_db->second.end()) {
				q.push(node);
			}
		}
		return move(res);
	}

	// @param user_id an integer
	// return a list of 10 new posts recently
	// and sort by timeline
	vector<Tweet>  getTimeline(int user_id) {
		// Write your code here
		vector<Tweet> res;
		auto it_db = tweets_db_.find(user_id);
		if (it_db == tweets_db_.end()) {
			return move(res);
		}
		int cnt = 0;
		for (const auto &tw : it_db->second) {
			res.push_back(tw.second);
			if (++cnt >= feeds_num) {
				break;
			}
		}
		return move(res);
	}

	// @param from_user_id an integer
	// @param to_user_id an integer
	// from user_id follows to_user_id
	void follow(int from_user_id, int to_user_id) {
		// Write your code here
		auto it_re = ft_relations_.find(from_user_id);
		if (it_re == ft_relations_.end()) {
			unordered_set<int> s;
			s.emplace(to_user_id);
			ft_relations_.emplace(from_user_id, move(s));
		}
		else {
			it_re->second.insert(to_user_id);
		}
	}

	// @param from_user_id an integer
	// @param to_user_id an integer
	// from user_id unfollows to_user_id
	void unfollow(int from_user_id, int to_user_id) {
		// Write your code here
		auto it_re = ft_relations_.find(from_user_id);
		if (it_re == ft_relations_.end()) {
			return;
		}
		it_re->second.erase(to_user_id);
	}

private:
	const int feeds_num = 10;

	unordered_map<int, map<time_t, Tweet>> tweets_db_;
	unordered_map<int, unordered_set<int>> ft_relations_;
	//unordered_map<int, unordered_set<int>> tf_relations_;

	class QueueNode {
	public:
		unordered_map<int, map<time_t, Tweet>>::iterator mIt_db;
		map<time_t, Tweet>::iterator mIt_tw;

		QueueNode(unordered_map<int, map<time_t, Tweet>>::iterator it_db, map<time_t, Tweet>::iterator it_tw) : mIt_db(it_db), mIt_tw(it_tw) {}
	};

	struct Compare {
		bool operator() (QueueNode &n1, QueueNode &n2) {
			return n1.mIt_tw->first < n2.mIt_tw->first;
		}
	};
};

int main() {
	MiniTwitter mtw;
	mtw.postTweet(1, "test1");
	mtw.postTweet(2, "test2");
	mtw.postTweet(1, "test3");
	vector<Tweet> tl1 = mtw.getTimeline(1);
	mtw.follow(2, 1);
	mtw.postTweet(2, "test4");
	mtw.postTweet(2, "test5");
	tl1 = mtw.getNewsFeed(1);
	tl1 = mtw.getNewsFeed(2);
	mtw.follow(1, 2);
	tl1 = mtw.getNewsFeed(1);
	mtw.unfollow(1, 2);
	tl1 = mtw.getNewsFeed(1);
	mtw.unfollow(1, 2);
	tl1 = mtw.getNewsFeed(1);
}