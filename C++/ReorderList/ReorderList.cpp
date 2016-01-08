/*
* see http://www.lintcode.com/en/problem/reorder-list/ for problem description
*/
#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <string> 

using namespace std;

class ListNode {
	public:
		int val;
		ListNode *next;
		ListNode(int val) {
			this->val = val;
			this->next = NULL;
			
		}		
};

class Solution {
public:
	/**
	* @param head: The first node of linked list.
	* @return: void
	*/
	void reorderList(ListNode *head) {
		if (!head) {
			return;
		}
		// find mid node first
		ListNode *slowP = head, *fastP = head->next;
		while (fastP && fastP->next) {
			slowP = slowP->next;
			fastP = fastP->next->next;
		}
		//break first and second half
		ListNode *midNode = slowP;
		slowP = slowP->next;
		midNode->next = NULL;
		//reverse second half
		ListNode midDummy(-1);
		while (slowP) {
			ListNode *tmp = slowP->next;
			slowP->next = midDummy.next;
			midDummy.next = slowP;
			slowP = tmp;
		}
		//merge first and reversed second half
		slowP = head;
		fastP = midDummy.next;
		while (slowP && fastP) {
			ListNode *tmp1 = slowP->next;
			ListNode *tmp2 = fastP->next;
			slowP->next = fastP;
			fastP->next = tmp1;
			slowP = tmp1;
			fastP = tmp2;
		}
	}
};

int main() {
	Solution s;

	ListNode n1(1);
	ListNode n2(2);
	ListNode n3(3);
	ListNode n4(4);
	ListNode n5(5);

	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	n4.next = &n5;

	s.reorderList(&n1);

	return 0;
}