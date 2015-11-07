#include<unordered_map>

using namespace std;

struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
	
};

RandomListNode *copyRandomList(RandomListNode *head) {
	// write your code here
	if (!head) {
		return head;
	}

	RandomListNode dummy(0);
	unordered_map<RandomListNode*, RandomListNode*> map;

	RandomListNode *pre = &dummy;
	RandomListNode *newNode;

	while (head) {
		//copy next
		if (map.find(head) == map.end()) {
			newNode = new RandomListNode(head->label);
			map[head] = newNode;
		}
		else {
			newNode = map[head];
		}

		pre->next = newNode;

		//copy random
		if (head->random) {
			if (map.find(head->random) == map.end()) {
				newNode = new RandomListNode(head->random->label);
				map[head->random] = newNode;
			}
			else {
				newNode = map[head->random];
			}

			pre->next->random = newNode;
		}

		pre = pre->next;
		head = head->next;
	}

	return dummy.next;
}

int main() {
	RandomListNode head(-1);

	copyRandomList(&head);

	return 0;
}