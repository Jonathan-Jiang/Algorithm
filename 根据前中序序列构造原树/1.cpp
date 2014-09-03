//
// 根据一棵树的前序、中序遍历序列重新构建树
//

#include <iostream>
#include <string>
using	namespace	std;
 
typedef struct Tree {
	char data;
	struct Tree * lchild, *  rchild;
} BiTree, * ptrBiTree;

ptrBiTree func(string preSeq, string inSeq, int sPre, int ePre, int sIn, int eIn) {
	ptrBiTree node = new BiTree;
	char root = preSeq[sPre];
	node->data = root;
	int index = inSeq.find(root);
	int lengthOfLchild = index - sIn;
	int lengthOfRchild = eIn - index;

	if (lengthOfLchild > 0) {
		node->lchild = func(preSeq, inSeq, sPre + 1, sPre + lengthOfLchild, sIn, sIn + lengthOfLchild - 1);
	} else {
		node->lchild = NULL;
	}

	if (lengthOfRchild > 0) {
		node->rchild = func(preSeq, inSeq, sPre + lengthOfLchild + 1, sPre + lengthOfLchild + lengthOfRchild, index + 1, index + lengthOfRchild);
	} else {
		node->rchild = NULL;
	}

	return node;
}

void mid(ptrBiTree root) {
	if (root->lchild) {
		mid(root->lchild);
	}

	cout << root->data;

	if (root->rchild) {
		mid(root->rchild);
	}	
}

int main() {
	string preSeq = "12456738";
	string inSeq = "42657183";

	ptrBiTree ROOT = func(preSeq, inSeq, 0, preSeq.length() - 1, 0, inSeq.length() - 1);

	mid(ROOT);
	cout << endl;

	return 0;
}
