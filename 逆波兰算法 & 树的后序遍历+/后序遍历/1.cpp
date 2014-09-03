#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using    namespace    std;

class TreeNode {
public:
    TreeNode(int p_data, bool p_is_op = true) : data(p_data), is_op(p_is_op), lchild(NULL), rchild(NULL) {}
	bool is_op;
	int data;
    TreeNode *lchild, *rchild;
};

TreeNode *constrcutTree() {
    TreeNode *root = new TreeNode('-');
    root->lchild = new TreeNode('*');
    root->rchild = new TreeNode('+');
    root->lchild->lchild = new TreeNode(6, false);
    root->lchild->rchild = new TreeNode(2, false);
    root->rchild->lchild = new TreeNode(8, false);
    root->rchild->rchild = new TreeNode(4, false);
    return root;
}

void print1(TreeNode* node) {
	if (node->is_op)
		cout << (char)node->data << " ";
	else
		cout << node->data << " ";
}

void print2(int num) {
	cout << num << " ";
}

// 递归得到后根遍历
void getList1_1(TreeNode* node, vector<TreeNode*> &list1_1) {
    if (node->lchild)
        getList1_1(node->lchild, list1_1);

    if (node->rchild)
        getList1_1(node->rchild, list1_1);

    list1_1.push_back(node);
}

// 非递归得到后根遍历
void getList1_2(TreeNode* root, vector<TreeNode*> &list1_2) {
	stack<TreeNode*> st;
	TreeNode* last_vist = NULL;

	TreeNode* cur_node = root;
	while (cur_node || !st.empty()) {
		while (cur_node) {
			st.push(cur_node);
			cur_node = cur_node->lchild;
		}

		cur_node = st.top();
		
		if (!cur_node->rchild || last_vist == cur_node->rchild) {
			list1_2.push_back(cur_node);
			last_vist = st.top();
			st.pop();
			cur_node = NULL;
		} else cur_node = cur_node->rchild;
	}
}

// 根据第一个链表得到第二个链表
void getList2(vector<TreeNode*> &list1, vector<int> &list2) {
	stack<int> st;
	for (vector<TreeNode*>::iterator it = list1.begin(); it != list1.end(); ++it) {
		if ((*it)->is_op) {
			int num1 = st.top();
			st.pop();
			int num2 = st.top();
			st.pop();

			if ((*it)->data == '-') {
				st.push(num1 - num2);
				list2.push_back(num1 - num2);
			} else if ((*it)->data == '+') {
				st.push(num1 + num2);
				list2.push_back(num1 + num2);
			} else if ((*it)->data == '*') {
				st.push(num1 * num2);
				list2.push_back(num1 * num2);
			}
		} else st.push((*it)->data);
	}
}


int main(int argc, char* const argv[]) {
    vector<TreeNode*> list1_1;
	vector<TreeNode*> list1_2;
    TreeNode *root = constrcutTree();

    // 递归算法
    getList1_1(root, list1_1);
    for_each(list1_1.begin(), list1_1.end(), print1);
	cout << endl;

    // 非递归算法
	getList1_2(root, list1_2);
	for_each(list1_2.begin(), list1_2.end(), print1);
	cout << endl;

	vector<int> list2;
	getList2(list1_1, list2);

	for_each(list2.begin(), list2.end(), print2);
	cout << endl;

    return 0;
}
