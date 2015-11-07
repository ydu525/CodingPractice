#include <unordered_map>
#include <vector>

using namespace std;

struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};


UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
	// write your code here
	if (!node) {
		return node;
	}

	unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> map;
	vector<UndirectedGraphNode*> nodes;

	nodes.push_back(node);
	map[node] = new UndirectedGraphNode(node->label);

	int start = 0;
	while (start < nodes.size()) {

		UndirectedGraphNode *curNode = nodes[start++];
		for (int i = 0; i < curNode->neighbors.size(); ++i) {

			UndirectedGraphNode *tmpNode = curNode->neighbors[i];
			if (map.find(tmpNode) == map.end()) {
				//not found
				nodes.push_back(tmpNode);
				map[tmpNode] = new UndirectedGraphNode(tmpNode->label);
			}
		}
	}

	for (auto node : nodes) {
		UndirectedGraphNode *cpyNode = map[node];
		for (int i = 0; i < node->neighbors.size(); ++i) {
			cpyNode->neighbors.push_back(map[map[node->neighbors[i]]]);
		}
	}

	return map[node];

}

int main() {
	UndirectedGraphNode n1(-1);
	UndirectedGraphNode n2(1);
	n1.neighbors.push_back(&n2);

	cloneGraph(&n1);

	return 0;
}

