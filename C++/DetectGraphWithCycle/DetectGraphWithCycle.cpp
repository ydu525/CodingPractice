#include <iostream>

#include <vector>

#include <string>

#include <istream>

#include <map>

using namespace std;

class Node {

public:

	Node(string l) : label(l) {}

	string label;

	vector<Node *> childNodes;

};

bool isGraphAcycle(vector<Node> graph) {

	return false;

}

int main() {

	/* Enter your code here. Read input from STDIN. Print output to STDOUT */

	vector<Node> graph;

	map<string, Node *> hash;

	size_t pos1, pos2;

	string tStr;

	string tStr2;

	string line;

	//parse the input

	while (getline(cin, line)) {

		pos1 = line.find_first_of(':');

		tStr = line.substr(0, pos1 - 0);

		if (hash.find(tStr) == hash.end()) {

			graph.emplace_back(tStr);

			hash[tStr] = &graph.back();

			cout << hash[tStr]->label << endl;

		}

		pos2 = line.find_first_of(',', ++pos1);

		while (pos2 != string::npos) {

			cout << "loop " << endl;

			//tmp.childNodes.push_back(line.substr(pos1, pos2 - pos1));

			tStr2 = line.substr(pos1, pos2 - pos1);

			cout << "tStr2 " << tStr2 << endl;

			if (hash.find(tStr2) == hash.end()) {

				graph.emplace_back(tStr2);

				hash[tStr2] = &graph.back();

				cout << hash[tStr2]->label << endl;

			}

			cout << "tStr2 push" << endl;

			hash[tStr]->childNodes.push_back(hash[tStr2]);

			cout << "tStr2 push finished" << endl;

			//insert(hash, tStr, tStr2);

			pos1 = pos2 + 1;

			if (pos1 >= line.size()) {

				cout << "break " << endl;

				break;

			}

			pos2 = line.find_first_of(',', pos1);

		}

		cout << "out " << endl;

		if (pos1 < line.size()) {

			//tmp.childNodes.push_back(line.substr(pos1, line.size() - pos1));

			string tStr2 = line.substr(pos1, line.size() - pos1);

			cout << "tStr2 " << tStr2 << endl;

			if (hash.find(tStr2) == hash.end()) {

				//Node tmp(tStr2);

				graph.emplace_back(tStr2);

				hash[tStr2] = &graph.back();

				cout << hash[tStr2]->label << endl;

			}

			hash[tStr]->childNodes.push_back(hash[tStr2]);

		}

		//graph.push_back(tmp);        

	}



	for (auto n : graph) {

		cout << n.label << ":";

		for (auto c : graph.back().childNodes) {

			cout << c->label << ",";

		}

		cout << endl;

	}

	return 0;

}