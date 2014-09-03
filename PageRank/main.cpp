#include <iostream>
#include <vector>
#include <string>
#include "PageRank.h"

using namespace std;

struct _pair {
	int from;
	int to;

	_pair(int _from, int _to) {
		from = _from;
		to = _to;
	}
};

bool contains(Node* node, vector<Node*>& nodes) {
	bool find = false;
	for (vector< Node* >::iterator iter = nodes.begin(); iter != nodes.end(); ++iter) {
		if ((*iter)->GetName() == node->GetName()) {
			find = true;
			break;
		}
	}
	return find;
}

bool findPair(_pair* p, vector< _pair* >& pairSet) {
	bool find = false;
	for (vector< _pair* >::iterator iter = pairSet.begin(); iter != pairSet.end(); ++iter) {
		if ((*iter)->from == p->from && (*iter)->to == p->to) {
			find = true;
			break;
		}
	}
	return find;
}

vector< Node* >::iterator getIter(Node* node, vector<Node*>& nodes) {
	for (vector< Node* >::iterator iter = nodes.begin(); iter != nodes.end(); ++iter) {
		if ((*iter)->GetName() == node->GetName())
			return iter;
	}
}

bool cmpPageRank(Node* a, Node* b) {
	return a->GetPageRank() > b->GetPageRank();
}

bool cmpPriority(Node* a, Node* b) {
	return a->GetPriority() > b->GetPriority();
}

void InitGraph(vector<Node*> & nodes) 
{
	// 邻接表存储方式
	FILE* fp = fopen("E:\\1.txt", "rb");
	int fromNodeId, toNodeId;
	vector< _pair* > pairSet;
	while (fscanf(fp, "%d%d", &fromNodeId, &toNodeId) != EOF) {
		Node* _nodeFrom = new Node(fromNodeId);
		Node* _nodeTo = new Node(toNodeId);

		_pair* curP = new _pair(toNodeId, fromNodeId);
		_pair* curP_reverse = new _pair(fromNodeId, toNodeId);

		if (!findPair(curP_reverse, pairSet)) {
			pairSet.push_back(curP);
			if (!contains(_nodeFrom, nodes) && !contains(_nodeTo, nodes)) {
				nodes.push_back(_nodeFrom);
				nodes.push_back(_nodeTo);
				_nodeTo->InsertLinkdInNode(_nodeFrom);
				_nodeFrom->InsertLinkdInNode(_nodeTo);
			} else if (!contains(_nodeFrom, nodes) && contains(_nodeTo, nodes)) {
				nodes.push_back(_nodeFrom);
				vector< Node* >::iterator iter = getIter(_nodeTo, nodes);
				(*iter)->InsertLinkdInNode(_nodeFrom);
				_nodeFrom->InsertLinkdInNode(*iter);
				delete _nodeTo;
			} else if (contains(_nodeFrom, nodes) && !contains(_nodeTo, nodes)) {
				nodes.push_back(_nodeTo);
				vector< Node* >::iterator iter = getIter(_nodeFrom, nodes);
				(*iter)->InsertLinkdInNode(_nodeTo);
				_nodeTo->InsertLinkdInNode(*iter);
				delete _nodeFrom;
			} else if (contains(_nodeFrom, nodes) && contains(_nodeTo, nodes)) {
				vector< Node* >::iterator iterFrom = getIter(_nodeFrom, nodes);
				vector< Node* >::iterator iterTo = getIter(_nodeTo, nodes);
				(*iterFrom)->InsertLinkdInNode(*iterTo);
				(*iterTo)->InsertLinkdInNode(*iterFrom);
				delete _nodeFrom;
				delete _nodeTo;
			}
		} else {
			delete curP;
		}
		delete curP_reverse;
	}
	pairSet.clear();
	fclose(fp);
}

Node* priority_probing(vector< Node* >& nodes) {
	sort(nodes.begin(), nodes.end(), cmpPriority);
	Node* ret = *nodes.begin();
	ret->ResetPriority();
	for (vector< Node* >::iterator iter = nodes.begin() + 1; iter != nodes.end(); ++iter) {
		(*iter)->IncrementPriority();
	}
	return ret;
}

Node* proportional_probing(vector< Node* >& nodes) {
	return *nodes.begin();
}

void probe(vector< Node* >& nodes) {
	FILE* fp = fopen("E:\\2.txt", "rb");
	int fromNodeId, toNodeId, idToBeChoosed;
	set< Node* > curNodeSet;
	// choose different strategy
	// 1. proportional_probing
	// Node* nodeToBeChoosed = proportional_probing(nodes);

	// 2. priority_probing
	Node* nodeToBeChoosed = priority_probing(nodes);

	idToBeChoosed = nodeToBeChoosed->GetName();
	while (fscanf(fp, "%d%d", &fromNodeId, &toNodeId) != EOF) {
		if (fromNodeId == idToBeChoosed) {
			Node* _nodeTo = new Node(toNodeId);
			if (contains(_nodeTo, nodes)) {
				vector< Node* >::iterator iterTo = getIter(_nodeTo, nodes);
				curNodeSet.insert(*iterTo);
			} else {
				nodes.push_back(_nodeTo);
				curNodeSet.insert(_nodeTo);
			}
		}
	}

	nodeToBeChoosed->refreshEdge(curNodeSet);
	curNodeSet.clear();
}

int main(int argc, const char* * argv)
{
	// build graph
	cout << "Initialize Graph..." << endl;
	vector< Node* > nodes;
    InitGraph(nodes);
    PageRank pr;
    // 迭代 40 次计算 PageRank
	cout << "Computing..." << endl;
	pr.Calc(nodes, 40);
    pr.PrintPageRank(nodes);
	cout << "========" << endl;

	probe(nodes);
	cout << "proportional_probing" << endl;
	pr.Calc(nodes, 40);
    pr.PrintPageRank(nodes);

	system("pause");
	
    return 0;
}