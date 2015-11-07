#include <list>
#include <iostream>
#include <exception>

using namespace std;

struct Record {
	Record(int id, int c) : ID(id), count(c) {};
	int ID;
	int count;
};

class noSecondLeastPopular : public exception
{
	virtual const char* what() const throw()
	{
		return "no second least popular";
	}
};

class Solution{
public:
	void insertIDs(int id, list<Record> &records) {
		for (auto it = records.begin(); it != records.end(); ++it) {
			if (id == it->ID) {
				++it->count;
				return;
			}
		}
		records.push_back(Record(id, 1));
	}

	//assume k is the number of unique IDs, n is number of elements in IDs
	//	average run time	O(n*k)
	//	average memory		O(k)
	//		because we have traverse each item in IDs, that's O(n)
	//		and we have to insert item into our record list, that's O(k) every time
	//	best run time		O(n)		
	//	best memory			O(1)
	//		the IDs array has no unique item
	//	worst run time		O(n^2)
	//	worst memory		O(n)
	//		each item in the input array is unique
	//
	//alternatively we can use unsorted_map for saving our records, then we can improve
	//our run time. Since insert elements into the unsorted_map(hashtable) is approxmately O(1)
	//we iterate the IDs once (O(n)), and we iterate the unsorted_map once (O(k)), the result is O(n).
	//memory is O(k)
	//
	//also we can use map or priority_queue. After we iterate IDs once, we dont have to iterate records.
	//We can access/pop the first two elements in the map/priority_queue, that's O(1).
	//But every time we inserting new ID into the record data structure takes O(logk), so that is O(n*logk) overall.
	//memory is O(k)
	int secondLeastPopular(const list<int> &IDs) {
		//empty
		//single
		//two items
		//all above senarios are impossible to have second least popular
		if (IDs.size() <= 2) {
			throw noSecondLeastPopular();
		}

		list<Record> records;

		for (auto it = IDs.begin(); it != IDs.end(); ++it) {
			insertIDs(*it, records);
		}
		
		Record least(-1, INT_MAX);
		Record secondLeast(-1, INT_MAX);
		for (auto it = records.begin(); it != records.end(); ++it) {
			if (it->count <= least.count) {
				if (it->count == least.count) {
					least.ID = tieBreaker(it->ID, least.ID);
				}
				else {
					secondLeast = least;
					least = *it;
				}
			}
			else if (it->count <= secondLeast.count) {
				if (it->count == secondLeast.count) {
					secondLeast.ID = tieBreaker(it->ID, secondLeast.ID);
				}
				else {
					secondLeast = *it;
				}
			}
		}

		if (secondLeast.ID == -1) {
			throw noSecondLeastPopular();
		}

		return secondLeast.ID;
	}

	int tieBreaker(int id1, int id2) {
		return id1 < id2 ? id1 : id2;
	}

	void test() {
		//test 1
		std::list<int> test1In;
		try {
			secondLeastPopular(test1In);
			cout << "test1 failed" << endl;
		}
		catch (noSecondLeastPopular e) {
			cout << "test1 passed" << endl;
		}
		catch (...) {
			cout << "test1 failed" << endl;
		}

		//test 2
		int test2Ints[] = {1};
		std::list<int> test2In(test2Ints, test2Ints + sizeof(test2Ints) / sizeof(int));
		try {
			secondLeastPopular(test2In);
			cout << "test2 failed" << endl;
		}
		catch (noSecondLeastPopular e) {
			cout << "test2 passed" << endl;
		}
		catch (...) {
			cout << "test2 failed" << endl;
		}
		

		//test 3
		int test3Ints[] = { 1, 2 };
		std::list<int> test3In(test3Ints, test3Ints + sizeof(test3Ints) / sizeof(int));
		try {
			secondLeastPopular(test3In);
			cout << "test3 failed" << endl;
		}
		catch (noSecondLeastPopular e) {
			cout << "test3 passed" << endl;
		}
		catch (...) {
			cout << "test3 failed" << endl;
		}

		//test 4
		int test4Ints[] = { 1, 2, 2 };
		std::list<int> test4In(test4Ints, test4Ints + sizeof(test4Ints) / sizeof(int));
		try {
			if (secondLeastPopular(test4In) == 2) {
				cout << "test4 passed" << endl;
			}
			else {
				cout << "test4 failed" << endl;
			}
		}
		catch (noSecondLeastPopular e) {
			cout << "test4 failed" << endl;
		}
		catch (...) {
			cout << "test4 failed" << endl;
		}

		//test 5
		int test5Ints[] = { 1, 2, 2, 3 };
		std::list<int> test5In(test5Ints, test5Ints + sizeof(test5Ints) / sizeof(int));
		try {
			if (secondLeastPopular(test5In) == 2) {
				cout << "test5 passed" << endl;
			}
			else {
				cout << "test5 failed" << endl;
			}
		}
		catch (noSecondLeastPopular e) {
			cout << "test5 failed" << endl;
		}
		catch (...) {
			cout << "test5 failed" << endl;
		}

		//test 6
		int test6Ints[] = { 1, 2, 3, 4 };
		std::list<int> test6In(test6Ints, test6Ints + sizeof(test6Ints) / sizeof(int));
		try {
			secondLeastPopular(test6In);
		}
		catch (noSecondLeastPopular e) {
			cout << "test6 passed" << endl;
		}
		catch (...) {
			cout << "test6 failed" << endl;
		}

		//test 7
		int test7Ints[] = { 1, 2, 2, 3, 3 };
		std::list<int> test7In(test7Ints, test7Ints + sizeof(test7Ints) / sizeof(int));
		try {
			if (secondLeastPopular(test7In) == 2) {
				cout << "test7 passed" << endl;
			}
			else {
				cout << "test7 failed" << endl;
			}
		}
		catch (noSecondLeastPopular e) {
			cout << "test7 failed" << endl;
		}
		catch (...) {
			cout << "test7 failed" << endl;
		}

		//test 8
		int test8Ints[] = { 1, 1, 1, 2, 3, 3 };
		std::list<int> test8In(test8Ints, test8Ints + sizeof(test8Ints) / sizeof(int));
		try {
			if (secondLeastPopular(test8In) == 3) {
				cout << "test8 passed" << endl;
			}
			else {
				cout << "test8 failed" << endl;
			}
		}
		catch (noSecondLeastPopular e) {
			cout << "test8 failed" << endl;
		}
		catch (...) {
			cout << "test8 failed" << endl;
		}

		//test 9
		int test9Ints[] = { 13, 13, 13, 6, 13, 13 };
		std::list<int> test9In(test9Ints, test9Ints + sizeof(test9Ints) / sizeof(int));
		try {
			if (secondLeastPopular(test9In) == 13) {
				cout << "test9 passed" << endl;
			}
			else {
				cout << "test9 failed" << endl;
			}
		}
		catch (noSecondLeastPopular e) {
			cout << "test9 failed" << endl;
		}
		catch (...) {
			cout << "test9 failed" << endl;
		}

		//test 10
		int test10Ints[] = { 4, 4, 4, 5, 6, 6, 7, 7, 8, 8, 8, 8 };
		std::list<int> test10In(test10Ints, test10Ints + sizeof(test10Ints) / sizeof(int));
		try {
			if (secondLeastPopular(test10In) == 6) {
				cout << "test10 passed" << endl;
			}
			else {
				cout << "test10 failed" << endl;
			}
		}
		catch (noSecondLeastPopular e) {
			cout << "test10 failed" << endl;
		}
		catch (...) {
			cout << "test10 failed" << endl;
		}
	}
};

int main() {
	Solution s;

	s.test();

	return 0;
}